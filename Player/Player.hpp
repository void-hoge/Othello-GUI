#ifndef PLAYER_HPP_INCLUDE
#define PLAYER_HPP_INCLUDE

#include "../Board/Board.hpp"
#include <iostream>

class Player{
public:
	void move(Board& board){
		uint64 mobility = board.checkMobility(board.getCurrentColor());
		if (mobility == 0) {
			std::cout << "pass" << '\n';
			board.pass();
			return;
		}
		std::cout << "move" << '\n';
		int x,y;
		hoge:;
		std::cin >> x >> y;
		// x = 8-x;
		// y = 8-y;
		uint64 mv = static_cast<uint64>(1) << x*8+y;

		if ((mv & mobility) == 0) {
			std::cout << "error" << '\n';
			goto hoge;
		}
		board.putDisc(mv);
		std::vector<int> coordinates;
		std::cout << board.history[board.getTurn()-1].putColor << '\n';
		coordinates = bm::expander(board.history[board.getTurn()-1].putPos);
		bm::outputCoordinate(coordinates[0]);
		coordinates.clear();
		coordinates = bm::expander(board.history[board.getTurn()-1].flippedDiscs);
		for (int i = 0; i < coordinates.size(); ++i) {
			bm::outputCoordinate(coordinates[i]);
		}
		std::cout << '\n';
		return;
	}
};

#endif //PLAYER_HPP_INCLUDE
