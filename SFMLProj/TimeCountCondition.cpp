#include "TimeCountCondition.h"
#include "StateMachineNode.h"

TimeCountCondition::TimeCountCondition(float time) : targTime(time), countedTime(0) { }
TimeCountCondition::~TimeCountCondition() { }

bool TimeCountCondition::conditionMet(StateMachineNode* stateMachine)
{
	// we're counting on this being polled once a frame..
	countedTime += stateMachine->getDt();

	// reset timer, complete condition
	if (countedTime >= targTime)
	{
		countedTime = 0;
		return true;
	}

	return false;
}
