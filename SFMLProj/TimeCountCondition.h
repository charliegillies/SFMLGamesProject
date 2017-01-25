#pragma once
#include "StateTransition.h"

/*
	Counts time everytime that the condition is polled with it's 
	condition met method. The condition is true if the appropiate
	amount of time has been counted.

	If inversed, this can also be a time limited condition.
*/
class TimeCountCondition : public StateTransition 
{
public:
	bool conditionMet(StateMachineNode* stateMachine) override;

	TimeCountCondition(float time);
	~TimeCountCondition();

private:
	float targTime;
	float countedTime;
};

