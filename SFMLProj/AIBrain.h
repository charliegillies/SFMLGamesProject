#pragma once
#include "AIState.h"

/*
	The brain is the personality of the AI.
*/
class AIBrain
{
public:
	AIBrain() {}
	virtual ~AIBrain() {}

	virtual AIState* getState() = 0;
};
