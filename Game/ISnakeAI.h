//allows various implementations of computer snake AI

#ifndef ISNAKEAI_H
#define ISNAKEAI_H

#include "Snake.h"
#include "../SolidMap.h"

class ISnakeAI
{
public:
	virtual void getMove(const Snake & snake, const SolidMap & solidMap);
};


#endif