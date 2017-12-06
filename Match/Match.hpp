#ifndef MATCH_HPP_INCLUDED
#define MATCH_HPP_INCLUDED

#include "../Board/Board.hpp"
#include "../AI/AI.hpp"
#include "../AI/AlphaBetaAI/AlphaBetaAI.hpp"
#include <vector>

class paramScore{
public:
	paramScore() : score(0){};
	int score;
	std::vector<int> param;
};

class Match{
private:
	Board board;
	AI *ai, *ia;
public:
	Match(){};
	void match(paramScore *param, paramScore *marap){
		ai = new AlphaBetaAI(param->param);
		ia = new AlphaBetaAI(marap->param);
		while(!board.isGameover()){
			// std::cout << "hoge" << '\n';
			std::cout << board.getTurn() << " ";
			ai->move(board);
			if (board.isGameover()){
				break;
			}
			std::cout << board.getTurn() << " ";
			ia->move(board);
		}
		color w = board.jadge();
		if (w == black) {
			param->score++;
			std::cout << "black won" << '\n';
		}else if(w == white){
			marap->score++;
			std::cout << "white won" << '\n';
		}
		delete ai;
		delete ia;
	};
};

#endif //MATCH_HPP_INCLUDED
