#pragma once
#include "AIState.h"

/*
	The brain is the master-controller of the AI.
	It considers what it should do next by working
	together with AIStates and the StateMachineNode.
*/
class AIBrain
{
public:
	AIBrain() {}
	virtual ~AIBrain() {}

	// the brain will consider what it should do next
	// be wary, this can return nullptr!
	virtual AIState* think() = 0;
};
