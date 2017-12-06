#ifndef PLAYER_HPP_INCLUDE
#define PLAYER_HPP_INCLUDE

#include "../Board/Board.hpp"
#include <iostream>

class Player{
public:
	void move(Board& board){
		hoge:;
		uint64 mobility = board.checkMobility(board.getCurrentColor());
		if (mobility == 0) {
			std::cout << "pass" << '\n';
			board.pass();
			return;
		}
		int x,y;
		std::cin >> x >> y;
		// x = 8-x;
		// y = 8-y;
		uint64 mv = static_cast<uint64>(1) << x*8+y;

		if ((mv & mobility) == 0) {
			std::cout << "そこには打てません。" << '\n';
			goto hoge;
		}
		board.putDisc(mv);
		// board.show();
		return;
	}
};

#endif //PLAYER_HPP_INCLUDE
