#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "../AI/AlphaBetaAI/AlphaBetaAI.hpp"
#include "../Player/Player.hpp"
#include <iostream>

inline void outputCoordinate(int n){
	std::cout << n / 8 << ',';
	std::cout << n % 8 << ' ';
	return;
}

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
		// std::cout << board.getTurn() << '\n';
		// std::cout << "AI's turn." << '\n';
		ai->move(board);
		if (board.history[board.getTurn()-1].pass == true) {
			std::cout << "pass" << '\n';
			return;
		}
		std::cout << "move" << '\n';
		std::vector<int> coordinates;
		std::cout << board.history[board.getTurn()-1].putColor << '\n';
		coordinates = bm::expander(board.history[board.getTurn()-1].putPos);
		outputCoordinate(coordinates[0]);
		coordinates.clear();
		coordinates = bm::expander(board.history[board.getTurn()-1].flippedDiscs);
		for (int i = 0; i < coordinates.size(); ++i) {
			outputCoordinate(coordinates[i]);
		}
		std::cout << '\n';
		return;
	}
	void playerMove(){
		// std::cout << board.getTurn() << '\n';
		// std::cout << "Player's turn" << '\n';
		player.move(board);
		// std::vector<int> coordinates;
		// std::cout << board.history[board.getTurn()-1].putColor << '\n';
		// coordinates = bm::expander(board.history[board.getTurn()-1].putPos);
		// outputCoordinate(coordinates[0]);
		// coordinates.clear();
		// coordinates = bm::expander(board.history[board.getTurn()-1].flippedDiscs);
		// for (int i = 0; i < coordinates.size(); ++i) {
		// 	outputCoordinate(coordinates[i]);
		// }
		// std::cout << '\n';
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
