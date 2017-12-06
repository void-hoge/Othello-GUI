#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "../AI/AlphaBetaAI/AlphaBetaAI.hpp"
#include "../Player/Player.hpp"
#include <iostream>

class Game{
private:
	Board board;
public:
	Game() : ai(new AlphaBetaAI()){}
	AI *ai;
	Player player;
	void aiMove(){
		std::cout << board.getTurn() << '\n';
		std::cout << "AI's turn." << '\n';
		ai->move(board);
		return;
	}
	void playerMove(){
		std::cout << board.getTurn() << '\n';
		std::cout << "Player's turn" << '\n';
		player.move(board);
		return;
	}
	void show(){
		board.show();
	}
};

#endif //GAME_HPP_INCLUDED
