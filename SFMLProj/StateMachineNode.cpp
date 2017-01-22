#include "StateMachineNode.h"

StateMachineNode::StateMachineNode() : _stateStack()
{
}

StateMachineNode::~StateMachineNode() {}

void StateMachineNode::start()
{
}

void StateMachineNode::update()
{
	if (_stateStack.empty())
	{
		return;
	}

	// get current state, execute it
	auto state = _stateStack.top();
	state->execute();

	// if we're complete..
	if (state->isComplete())
	{
		// exit this state
		state->onExit();
		// remove it from the stack
		_stateStack.pop();

		// if there are other states in the stack, enter it
		if (!_stateStack.empty())
			_stateStack.top()->onEnter();
	}
}

void StateMachineNode::pushState(AIState* state)
{
	if (_stateStack.size() > 0)
		_stateStack.top()->onExit();

	state->setStateMachine(this);
	_stateStack.push(state);
	state->onEnter();
}