#ifndef MIDEVALUATOR_HPP_INCLUDED
#define MIDEVALUATOR_HPP_INCLUDED

#include "../Evaluator.hpp"
#include "../../bitmanipulations/bitmanipulations.hpp"
namespace bm = bitmanipulations;

class MidEvaluator : public Evaluator{
public:
	MidEvaluator(std::vector<int> param) : Evaluator(param){};
	int evaluate(const Board& board){
		int mobilityScore = bm::bitCount(board.checkMobility(board.getCurrentColor()));
		int confirmedCellsScore = bm::bitCount(board.getConfirmedDiscs(board.getCurrentColor())) -  bm::bitCount(board.getConfirmedDiscs(1-board.getCurrentColor()));
		return mobilityScore*weight[0] + confirmedCellsScore*weight[1];
	};
};

#endif //MIDEVALUATOR_HPP_INCLUDED
