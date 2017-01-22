#pragma once
#include "AIState.h"

/*
	Handles the transition between states.
*/
class StateTransition
{
public:
	StateTransition() : _next(nullptr) {}
	virtual ~StateTransition() {}

	// Tests if the condition of the state transition
	// has been met. If it has, then call getNextState() 
	// to get the next state that this transition holds.
	virtual bool conditionMet() = 0;

	// Gets the next state that has been set inside of the .setState method.
	virtual AIState* getNextState()
	{
		return _next;
	}

	// Internally sets the 'next' state of the transition.
	// This is retrieved through 'getNextState()'
	void setState(AIState* state)
	{
		_next = state;
	}

private:
	AIState* _next;
};