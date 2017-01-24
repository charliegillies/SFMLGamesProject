#pragma once
#include "StateTransition.h"

/*
	Checks if we can or cannot shoot.
*/
class CanShootCondition : public StateTransition
{
public:
	bool conditionMet(StateMachineNode* stateMachine) override;

	CanShootCondition();
	~CanShootCondition();
};

