#ifndef MIDEVALUATOR_HPP_INCLUDED
#define MIDEVALUATOR_HPP_INCLUDED

#include "../Evaluator.hpp"
#include "../../bitmanipulations/bitmanipulations.hpp"
namespace bm = bitmanipulations;

class MidEvaluator : public Evaluator{
public:
	MidEvaluator(std::vector<int> param) : Evaluator(param){};
	int evaluate(const Board& board){
		int mobility = bm::bitCount(board.checkMobility(board.getCurrentColor())) - bm::bitCount(board.checkMobility(1-board.getCurrentColor()));
		int stable = bm::bitCount(board.getStableDiscs(board.getCurrentColor())) -  bm::bitCount(board.getStableDiscs(1-board.getCurrentColor()));
		int corner = bm::bitCount(board.getCornerDiscs(board.getCurrentColor())) - bm::bitCount(board.getCornerDiscs(1-board.getCurrentColor()));
		return mobility*weight[0] + stable*weight[1] + corner*weight[2];
	};
};

#endif //MIDEVALUATOR_HPP_INCLUDED
