#pragma once
#include "StateTransition.h"

/*
	Checks if the node is in distance of the start position.
*/
class InDistanceOfStartCondition : public StateTransition
{
public:
	bool conditionMet(StateMachineNode* stateMachine) override;

	InDistanceOfStartCondition(float range);
	~InDistanceOfStartCondition();

private:
	float range;
};

