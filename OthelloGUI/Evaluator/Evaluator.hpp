#ifndef EVALUATOR_HPP_INCLUDED
#define EVALUATOR_HPP_INCLUDED

#include "../Board/Board.hpp"
#include <iostream>
#include <vector>

class Evaluator{
protected:
	std::vector<int> weight;
public:
	Evaluator(){
		weight.push_back(1);
		weight.push_back(1);
		weight.push_back(1);
		weight.push_back(1);
		weight.push_back(1);
	};
	Evaluator(std::vector<int> param){
		weight = param;
	};
	~Evaluator(){};
	virtual int evaluate(const Board& board) = 0;
};

#endif //EVALUATOR_HPP_INCLUDED
