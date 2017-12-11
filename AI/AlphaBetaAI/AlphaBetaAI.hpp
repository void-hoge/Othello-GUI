#ifndef ALPHABETAAI_HPP_INCLUDED
#define ALPHABETAAI_HPP_INCLUDED

#include <vector>
#include <algorithm>
#include <iostream>
#include <bitset>
#include "../../Board/Board.hpp"
#include "../AI.hpp"
#include "../../Evaluator/Evaluator.hpp"
#include "../../Evaluator/MidEvaluator/MidEvaluator.hpp"
#include "../../Evaluator/PerfectEvaluator/PerfectEvaluator.hpp"
#include "../../Evaluator/WLDEvaluator/WLDEvaluator.hpp"
#include "../../bitmanipulations/bitmanipulations.hpp"

namespace bm = bitmanipulations;

const int intmax = 2147483647;

class AlphaBetaAI : public AI{
public:
	AlphaBetaAI(){
		param.push_back(1);
		param.push_back(1);
		param.push_back(1);
	};
	AlphaBetaAI(std::vector<int> param) : param(param){
	};
	inline void move(Board& board){
		board.initArray();
		uint64 mobility = board.currentCheckMobility();
		if (mobility == 0){
			board.pass();
			return;
		}
		if (bm::bitCount(mobility) == 1){
			board.putDisc(mobility);
			std::cout << "move" << '\n';
			return;
		}
		int limit;
		Eval = new MidEvaluator(param);
		sort(board, presearchDepth);
		int eval, alpha = -intmax, beta = intmax;
		posEval p;
		if (bm::bitCount(board.getBlank()) <= wldDepth){
			limit = intmax;
			if (bm::bitCount(board.getBlank()) <= perfectDepth) {
				Eval = new PerfectEvaluator();
			}	else{
				Eval = new WLDEvaluator();
			}
		}	else{
			limit = normalDepth;
		}
		for (int i = 0; i < board.getMovableSize(); ++i){
			board.putDisc(board.currentPoint[i].pos);
			eval = -alphabeta(board, limit-1, -beta, -alpha);
			board.undo();
			if (eval > alpha){
				alpha = eval;
				p = board.currentPoint[i];
			}
		}
		delete Eval;
		Eval = NULL;
		board.putDisc(p.pos);
		std::cout << "move" << '\n';
		return;
	};
private:
	std::vector<int> param;
	Evaluator* Eval;
	void sort(Board& board, const int limit){
		for (int i = 0; i < board.getMovableSize(); ++i){
			int eval;
			board.putDisc(board.currentPoint[i].pos);
			eval = -alphabeta(board, limit-1, -intmax, intmax);
			board.undo();
			board.currentPoint[i].eval = eval;
		}
		std::stable_sort(&board.currentPoint[0], &board.currentPoint[board.getMovableSize()], comp);
		return;
	};
	int alphabeta(Board& board, int limit, int alpha, int beta){
		if (limit == 0){
			return Eval->evaluate(board);
		}
		uint64 currentMovablePos = board.currentCheckMobility();
		int score;
		if (currentMovablePos == 0){
			if (board.antiCurrentCheckMobility() == 0){
				return Eval -> evaluate(board);
			}
			board.pass();
			score = -alphabeta(board, limit, -beta, -alpha);
			board.undo();
			return score;
		}
		for (int i = 0; i < board.getMovableSize(); ++i){
			board.putDisc(board.currentPoint[i].pos);
			score = -alphabeta(board, limit-1, -beta, -alpha);
			board.undo();

			if (score >= beta){
				return score;
			}

			alpha = std::max(alpha, score);
		}
		return alpha;
	};
};

#endif //ALPHABETAAI_HPP_INCLUDED
