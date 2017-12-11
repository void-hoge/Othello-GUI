#ifndef BOARD_HPP_INCLUDED
#define BOARD_HPP_INCLUDED

#include "../bitmanipulations/bitmanipulations.hpp"
#include <vector>
#include <array>
namespace bm = bitmanipulations;

typedef int color;
const color white = 0;
const color black = 1;
const color empty = -1;
const color draw  = 2;

class Log{
public:
	uint64 flippedDiscs;
	uint64 putPos;
	color putColor;
	bool pass;
	int movableSize;
	Log(){
		init();
	}
	void init(){
		flippedDiscs = 0;
		putPos = 0;
		putColor = empty;
		pass = false;
		movableSize = 0;
	}
};

struct posEval{
	uint64 pos;
	int eval;
};

inline bool comp(const posEval a, const posEval b){
	return a.eval > b.eval;
}

class Board{
public:
	Board(){
		data[black] = 0b0000000000000000000000000000100000010000000000000000000000000000;
		data[white] = 0b0000000000000000000000000001000000001000000000000000000000000000;
		turn = 0;
		currentColor = black;
		movablesArray = (posEval*)std::malloc(sizeof(posEval)*512);
		if (movablesArray == NULL) {
			std::cout << "ERROR!!!" << '\n';
		}
		currentPoint = movablesArray;
	}

	~Board(){
		std::free(movablesArray);
	}

	uint64 getBoard(color c) const{
		return data[c];
	};

	bool isGameover() const{
		if ((checkMobility(white) | checkMobility(black)) == 0){
			return true;
		}
		return false;
	};
	color jadge() const{
		if (isGameover() == false) {
			return empty;
		}
		if (countDiscs(white) < countDiscs(black)) {
			return black;
		}
		if (countDiscs(white) > countDiscs(black)) {
			return white;
		}
		return draw;
	};
	uint64 checkMobility(color c) const{
		using namespace bm;
		//left
		uint64 	o = (data[c] & 0x7F7F7F7F7F7F7F7F) << 1,
				p = data[1-c] & 0xFEFEFEFEFEFEFEFE;
		uint64 left = (~(p | o) & (p + o)) & 0xFEFEFEFEFEFEFEFE;

		//right
		o = (horizontalMirror(data[c]) & 0x7F7F7F7F7F7F7F7F) << 1;
		p = horizontalMirror(data[1-c]) & 0xFEFEFEFEFEFEFEFE;
		uint64 right = horizontalMirror((~(p | o) & (p + o)) & 0xFEFEFEFEFEFEFEFE);

		//upper
		o = (diagonalMirror45(data[c]) & 0x7F7F7F7F7F7F7F7F) << 1;
		p = diagonalMirror45(data[1-c]) & 0xFEFEFEFEFEFEFEFE;
		uint64 upper = diagonalMirror45((~(p | o) & (p + o)) & 0xFEFEFEFEFEFEFEFE);

		//lower
		o = (diagonalMirror135(data[c]) & 0x7F7F7F7F7F7F7F7F) << 1;
		p = diagonalMirror135(data[1-c]) & 0xFEFEFEFEFEFEFEFE;
		uint64 lower = diagonalMirror135((~(p | o) & (p + o)) & 0xFEFEFEFEFEFEFEFE);

		//lowerLeft
		o = (slashConv(data[c] & ~0x80808080808080FF)) << 1;
		p = slashConv(data[1-c] & ~0xFF01010101010101);
		uint64 lowerLeft = backSlashConv(~(p | o) & (p + o)) & ~0xFF01010101010101;

		//upperLeft
		o = (backSlashConv(data[c] & ~0xFF80808080808080)) << 1;
		p = backSlashConv(data[1-c] & ~ 0x01010101010101FF);
		uint64 upperLeft = slashConv(~(p | o) & (p + o)) & ~0x01010101010101FF;

		//lowerRight
		o = (slashConv(horizontalMirror(data[c] & ~0x01010101010101FF))) << 1;
		p = slashConv(horizontalMirror(data[1-c] & ~0xFF80808080808080));
		uint64 lowerRight = horizontalMirror(backSlashConv(~(p | o) & (p + o))) & ~0xFF80808080808080;

		//upperRight
		o = (backSlashConv(horizontalMirror(data[c] & ~0xFF01010101010101))) << 1;
		p = backSlashConv(horizontalMirror(data[1-c] & ~0x80808080808080FF));
		uint64 upperRight = horizontalMirror(slashConv(~(p | o) & (p + o))) & ~0x80808080808080FF;

		uint64 blank = ~(data[white] | data[black]);
		return (left | right | upper | lower | upperLeft | upperRight | lowerLeft | lowerRight) & blank;
	};
	uint64 currentCheckMobility() {
		uint64 mobility = checkMobility(currentColor);
		history[turn].movableSize = movablesExpander(mobility);
		return mobility;
	};
	uint64 getBlank(){
		return ~(data[white]|data[black]);
	};
	uint64 antiCurrentCheckMobility() {
		return checkMobility(1-currentColor);
	};
	bool putDisc(const uint64 mv){
		color c = currentColor;

		uint64 rev = getFlipDiscs(mv, c);
		if (rev == 0) {
			return false;
		}
		data[c] ^= rev | mv;
		data[1-c] ^= rev;

		currentColor = 1-currentColor;

		history[turn].flippedDiscs = rev;
		history[turn].putPos = mv;
		history[turn].putColor = c;

		currentPoint = &currentPoint[history[turn].movableSize];

		turn++;
		return true;
	};
	bool undo(){
		if (turn == 0) {
			std::cout << "cannot undo" << '\n';
			return false;
		}


		turn--;

		if (history[turn].pass) {
			currentColor = history[turn].putColor;
			history[turn].init();
			return true;
		}

		uint64 rev = history[turn].flippedDiscs;
		data[history[turn].putColor] ^= rev | history[turn].putPos;
		data[1-(history[turn].putColor)] ^= rev;
		currentColor = history[turn].putColor;

		currentPoint = &currentPoint[-history[turn].movableSize];

		return true;
	}

	bool pass(){
		history[turn].pass = true;
		history[turn].putColor = currentColor;

		currentColor = 1-currentColor;
		turn++;
		return true;
	}

	posEval *movablesArray;
	posEval *currentPoint;

	void initArray() {
		currentPoint = movablesArray;
		return;
	};
	uint64 getStableDiscs(color c) const{
		using namespace bm;
		uint64 left = data[c] & 0xFF000000000000FF;
		uint64 s = left + 0x0100000000000001;
		left = (left ^ s) & ~s;

		uint64 right = horizontalMirror(data[c]) & 0xFF000000000000FF;
		s = right + 0x0100000000000001;
		right = (right ^ s) & ~s;

		uint64 upper = diagonalMirror135(data[c]) & 0xFF000000000000FF;
		s = upper + 0x0100000000000001;
		upper = (upper ^ s) & ~s;

		uint64 lower = diagonalMirror45(data[c]) & 0xFF000000000000FF;
		s = lower + 0x0100000000000001;
		lower = (lower ^ s) & ~s;

		return left + right + upper + lower;
	};
	uint64 getCornerDiscs(color c) const{
		return data[c] & 0x8100000000000018;
	};
	int countDiscs(const color c) const{
		return bitmanipulations::bitCount(data[c]);
	};
	color check(unsigned coordinate) const{
		if ((((uint64)1 << coordinate) & data[white]) != 0) {
			return white;
		}
		if ((((uint64)1 << coordinate) & data[black]) != 0) {
			return black;
		}
		return empty;
	};
	color getCurrentColor() const{
		return currentColor;
	};
	int getTurn() const{
		return turn;
	};
	int countDiscs(color c){
		return bitmanipulations::bitCount(data[c]);
	};
	int getMovableSize(){
		return history[turn].movableSize;
	};
	void show(){
		color c;
		std::cout << "  0 1 2 3 4 5 6 7" << '\n';
		for (int i = 0; i < 8; i++) {
			std::cout << i;
			for (int j = 0; j < 8; j++) {
				c = check(i * 8 + j);
				if (c == empty) {
					std::cout << "  ";
				}
				if (c == white) {
					std::cout << " o";
				}
				if (c == black) {
					std::cout << " *";
				}
			}
			std::cout << "" << '\n';
		}
		return;
	};
	std::array<Log, 80> history;
private:
	uint64 data[2];
	int turn;
	color currentColor;
	uint64 getFlipDiscs(uint64 put, color c) const{
		using namespace bm;
		//left
		uint64 	o = data[c],
				p = data[1-c],
				q = (put & 0x7F7F7F7F7F7F7F7F) << 1;
		uint64 left = p^((p + q) & ~q & ~o);
		left *= ((left & ~0x7F7F7F7F7F7F7F7F) == 0) * (((p + q) & o) != 0);

		//right
		o = horizontalMirror(data[c]);
		p = horizontalMirror(data[1-c]);
		q = (horizontalMirror(put & 0xFEFEFEFEFEFEFEFE)) << 1;
		uint64 right = horizontalMirror(p^((p + q) & ~q & ~o));
		right *= ((right & ~0xFEFEFEFEFEFEFEFE) == 0) * (((p + q) & o) != 0);

		//upper
		o = diagonalMirror45(data[c]);
		p = diagonalMirror45(data[1-c]);
		q = (diagonalMirror45(put & 0xFFFFFFFFFFFFFF00)) << 1;
		uint64 upper = diagonalMirror45(p^((p + q) & ~q & ~o));
		upper *= ((upper & ~0xFFFFFFFFFFFFFF00) == 0) * (((p + q) & o) != 0);

		//lower
		o = diagonalMirror135(data[c]);
		p = diagonalMirror135(data[1-c]);
		q = (diagonalMirror135(put & 0x00FFFFFFFFFFFFFF)) << 1;
		uint64 lower = diagonalMirror135(p^((p + q) & ~q & ~o));
		lower *= ((lower & ~0x00FFFFFFFFFFFFFF) == 0) * (((p + q) & o) != 0);

		//lowerLeft
		o = slashConv(data[c]);
		p = slashConv(data[1-c]);
		q = (slashConv(put & ~0x80808080808080FF)) << 1;
		uint64 lowerLeft = backSlashConv(p^((p + q) & ~q & ~o));
		lowerLeft *= ((lowerLeft & 0x80808080808080FF) == 0) * (((p + q) & o) != 0);

		//upperLeft
		o = backSlashConv(data[c]);
		p = backSlashConv(data[1-c]);
		q = (backSlashConv(put & ~0xFF80808080808080)) << 1;
		uint64 upperLeft = slashConv(p^((p + q) & ~q & ~o));
		upperLeft *= ((upperLeft & 0xFF80808080808080) == 0) * (((p + q) & o) != 0);

		//upperRight
		o = slashConv(horizontalMirror(data[c]));
		p = slashConv(horizontalMirror(data[1-c]));
		q = (slashConv(horizontalMirror(put & ~0x1010101010101FF))) << 1;
		uint64 upperRight = horizontalMirror(backSlashConv(p^((p + q) & ~q & ~o)));
		upperRight *= ((upperRight & 0x1010101010101FF) == 0) * (((p + q) & o) != 0);

		//lowerRight
		o = backSlashConv(horizontalMirror(data[c]));
		p = backSlashConv(horizontalMirror(data[1-c]));
		q = (backSlashConv(horizontalMirror(put & ~0xFF01010101010101))) << 1;
		uint64 lowerRight = horizontalMirror(slashConv(p^((p + q) & ~q & ~o)));
		lowerRight *= ((lowerRight & 0xFF01010101010101) == 0) * (((p + q) & o) != 0);

		return left | right | upper | lower | upperLeft | upperRight | lowerLeft | lowerRight;
	}
	int movablesExpander(uint64 movablePos){
		if (movablePos == 0) {
			return 0;
		}
		int idx = 0;
		for (uint64 i = 1; i != 0; i <<= 1) {
			if ((movablePos & i) != 0) {
				currentPoint[idx].pos = i;
				idx++;
			}
		}
		return idx;
	};
};

#endif //BOARD_HPP_INCLUDED
