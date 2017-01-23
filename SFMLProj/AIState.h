#pragma once
#include "StateMachineNode.h"
#include "StateTransition.h"

class StateMachineNode;

/*
	Base header-only class of a state for a state machine.
*/
class AIState
{
public:
	AIState() {}
	virtual ~AIState() {}

	// all potential transitions
	std::vector<StateTransition*> transitions;

	// called when the state begins it's operations
	virtual void onEnter() = 0;

	// called every frame while state is operating
	virtual void execute() = 0;

	// called when the state has finished or is exited early
	virtual void onExit() = 0;

	// sets the internal reference to 
	// the state machine that owns the state
	void setStateMachine(StateMachineNode* stateMachine)
	{
		this->stateMachine = stateMachine;
	}

	// adds a transition to the internal transitions vector
	// this is a shorthand method that adds the state transitions next state
	// and returns the added state, so you can build methods onto one another
	AIState* addTransition(StateTransition* transition, AIState* state)
	{
		transition->setState(state);
		transitions.push_back(transition);
		return state;
	}

protected:
	StateMachineNode* stateMachine;
};

