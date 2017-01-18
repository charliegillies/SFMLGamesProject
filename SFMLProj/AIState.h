#pragma once
#include "StateMachineNode.h"

class StateMachineNode;

/*
	Base header-only class of a state for a state machine.
*/
class AIState
{
public:
	AIState() : complete(false) {}
	virtual ~AIState() {}

	// called when the state begins it's operations
	virtual void onEnter() {}

	// called every frame while state is operating
	virtual void execute() {}

	// called when the state has finished or is exited early
	virtual void onExit() {}

	// if the state has been complete internally or not
	bool isComplete()
	{
		return complete;
	}

	// sets the internal reference to 
	// the state machine that owns the state
	void setStateMachine(StateMachineNode* stateMachine)
	{
		this->stateMachine = stateMachine;
	}

protected:
	bool complete;
	StateMachineNode* stateMachine;
};

