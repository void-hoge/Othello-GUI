#ifndef AI_HPP_INCLUDED
#define AI_HPP_INCLUDED

#include "../Board/Board.hpp"

class AI{
protected:
	const unsigned presearchDepth;
	const unsigned normalDepth;
	const unsigned wldDepth;
	const unsigned perfectDepth;
public:
	AI() : presearchDepth(7), normalDepth(11), wldDepth(18), perfectDepth(0){
	}
	virtual void move(Board& board) = 0;
};

#endif //AI_HPP_INCLUDED
