//g++ main.cpp -std=c++17 -O3 -mtune=native -march=native -flto
#include "Game/Game.hpp"
#include "Match/Match.hpp"
#include <vector>
#include <iostream>

int main(int argc, char const *argv[]) {
	Game game;
	// game.show();
	while (!game.isGameover()) {
		// game.playerMove();
		game.aiMove();
		// game.show();
		if (game.isGameover()) {
			break;
		}
		game.aiMove();
		// game.show();
	}
	std::cout << "end" << '\n';
	return 0;
}
