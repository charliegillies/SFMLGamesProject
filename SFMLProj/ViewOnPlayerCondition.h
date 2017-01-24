#pragma once
#include "StateTransition.h"

class ViewOnPlayerCondition : public StateTransition
{
public:
	ViewOnPlayerCondition(float range);
	~ViewOnPlayerCondition();

	bool conditionMet(StateMachineNode* stateMachine) override;

private:
	float range;
};