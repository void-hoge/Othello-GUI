//g++ main.cpp -std=c++17 -O3 -mtune=native -march=native -flto
#include "Game/Game.hpp"
#include "Match/Match.hpp"
#include <vector>
#include <iostream>

int main(int argc, char const *argv[]) {
	Game game;
	game.show();
	for (int i = 0; i < 33; i++) {
		// game.playerMove();
		game.aiMove();
		game.show();
		game.aiMove();
		game.show();
	}
	return 0;
}
