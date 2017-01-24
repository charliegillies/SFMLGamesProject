#pragma once
#include "StateTransition.h"

/*
	Returns a fixed condition given inside of of the constructor.
	Use this for debugging and fixing weird state transition edge cases.
*/
class FixedCondition : public StateTransition
{
public:
	FixedCondition(bool result) : result(result) {};
	~FixedCondition() {}
	
	bool conditionMet(StateMachineNode* stateMachine) override
	{
		return result;
	}

private:
	bool result;
};

