#pragma once

class AIState;
class StateMachineNode;

/*
	Handles the transition between states.
*/
class StateTransition
{
public:
	StateTransition() : _next(nullptr), viewAsInverse(false) {}
	virtual ~StateTransition() {}

	// If conditionMet() should be viewed as an inverse value.
	// e.g. if true = false, false = true. this stops us from
	// having to create many conditions for boolean alternatives
	bool viewAsInverse;

	// Tests if the condition of the state transition
	// has been met. If it has, then call getNextState() 
	// to get the next state that this transition holds.
	virtual bool conditionMet(StateMachineNode* stateMachine) = 0;

	// Gets the next state that has been set inside of the .setState method.
	AIState* getNextState()
	{
		return _next;
	}

	// Internally sets the 'next' state of the transition.
	// This is retrieved through 'getNextState()'
	void setState(AIState* state)
	{
		_next = state;
	}

	// Internally sets the 'view as inverse' flag to true.
	StateTransition* toggleViewAsInverse()
	{
		viewAsInverse = true;
		return this;
	}

private:
	AIState* _next;
};