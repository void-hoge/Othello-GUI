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
		showLog();
		return;
	}
	void playerMove(){
		player.move(board);
		showLog();
		return;
	}
	void show(){
		board.show();
	}
	bool isGameover(){
		return board.isGameover();
	}
	void showLog(){
		if (board.history[board.getTurn()-1].pass == true) {
			std::cout << "pass" << '\n';
			return;
		}
		std::cout << "move" << '\n';
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
	}
};

#endif //GAME_HPP_INCLUDED
