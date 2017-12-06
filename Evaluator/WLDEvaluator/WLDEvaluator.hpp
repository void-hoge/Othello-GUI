#ifndef WLDEVALUATOR_HPP_INCLUDED
#define WLDEVALUATOR_HPP_INCLUDED

#include "../Evaluator.hpp"

class WLDEvaluator : public Evaluator{
public:
	static const int WIN = 1;
	static const int DRAW = 0;
	static const int LOSE = -1;
	int evaluate(const Board& board){
		int discdiff = board.countDiscs(board.getCurrentColor()) - board.countDiscs(1 - board.getCurrentColor());

		if (discdiff > 0) {
			return -WIN;
		}	else if(discdiff < 0){
			return LOSE;
		}	else{
			return -DRAW;
		}
	}
};

#endif
