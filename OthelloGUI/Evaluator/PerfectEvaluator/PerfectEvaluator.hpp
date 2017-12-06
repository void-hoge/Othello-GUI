#ifndef PERFECTEVALUATOR_HPP_INCLUDED
#define PERFECTEVALUATOR_HPP_INCLUDED

#include "../Evaluator.hpp"

class PerfectEvaluator : public Evaluator{
public:
	int evaluate(const Board& board){
		return board.countDiscs(board.getCurrentColor()) - board.countDiscs(1 - board.getCurrentColor());
	}
};

#endif
