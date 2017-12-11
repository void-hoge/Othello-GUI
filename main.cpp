//g++ main.cpp -std=c++17 -O3 -mtune=native -march=native -flto
#include "Game/Game.hpp"
#include "Match/Match.hpp"
#include <vector>
#include <iostream>

void sente(){
	Game game;
	game.showBoard();
	game.show();
	while (!game.isGameover()) {
		game.playerMove();
		game.show();
		if (game.isGameover()) {
			break;
		}
		game.aiMove();
		game.show();
	}
	std::cout << "end" << '\n';
}

void gote(){
	Game game;
	game.show();
	while (!game.isGameover()) {
		game.aiMove();
		game.show();
		if (game.isGameover()) {
			break;
		}
		game.playerMove();
		game.show();
	}
	std::cout << "end" << '\n';
}

int main(int argc, char const *argv[]) {
	int p;
	hoge:
	std::cin >> p;
	switch (p) {
		case 0:
			sente();
			break;
		case 1:
			gote();
			break;
		default:
			std::cout << "ERROR!" << '\n';
			goto hoge;
			break;
	}
	return 0;
}
