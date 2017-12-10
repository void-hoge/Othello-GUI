#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "../AI/AlphaBetaAI/AlphaBetaAI.hpp"
#include "../Player/Player.hpp"
#include <iostream>
#include "../bitmanipulations/bitmanipulations.hpp"

class Game{
private:
	Board board;
public:
	Game() : ai(new AlphaBetaAI()){}
	AI *ai;
	Player player;
	void setParam(){

	}
	void aiMove(){
		ai->move(board);
		return;
	}
	void playerMove(){
		player.move(board);
		return;
	}
	void show(){
		board.show();
	}
	bool isGameover(){
		return board.isGameover();
	}
};

#endif //GAME_HPP_INCLUDED
