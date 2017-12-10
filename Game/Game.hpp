#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "../AI/AlphaBetaAI/AlphaBetaAI.hpp"
#include "../Player/Player.hpp"
#include <iostream>
#include "vector"
#include "../bitmanipulations/bitmanipulations.hpp"

class Game{
private:
	Board board;
public:
	Game() : ai(new AlphaBetaAI()){}
	AI *ai;
	Player player;
	void showBoard(){
		std::vector<int> white_board;
		white_board = bm::expander(board.getBoard(white));
		std::cout << white << '\n';
		for (int i = 0; i < white_board.size(); i++) {
			bm::outputCoordinate(white_board[i]);
		}
		std::cout << '\n';
		std::vector<int> black_board;
		black_board = bm::expander(board.getBoard(black));
		std::cout << black << '\n';
		for (int i = 0; i < black_board.size(); i++) {
			bm::outputCoordinate(black_board[i]);
		}
		std::cout << '\n';
		return;
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
