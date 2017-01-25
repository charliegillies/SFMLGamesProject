#pragma once
#include "StateTransition.h"
#include <vector>

/*
	A condition that evaluates more than one child conditions.
	
	If all true flag is true, all children be true in order for conditionMet() to return true.
	If all true flag is false, any one condition will be enough for conditionMet() to return true.
*/
class MultiCondition : public StateTransition
{
public:
	MultiCondition(bool all_must_be_true);
	~MultiCondition();

	bool conditionMet(StateMachineNode* stateMachine) override;

	MultiCondition* addChild(StateTransition* child);

private:
	bool _allTrue;
	std::vector<StateTransition*> _children;
};

