#include "StateMachineNode.h"
#include "AIBrain.h"

StateMachineNode::StateMachineNode(AIBrain* brain) : _stateStack()
{
	_brain = brain;
}

StateMachineNode::~StateMachineNode() {}

void StateMachineNode::start()
{
	askBrain();
}

void StateMachineNode::update()
{
	if (_stateStack.empty())
	{
		askBrain();
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

void StateMachineNode::askBrain()
{
	auto state = _brain->think();
	if (state == nullptr) return;

	pushState(state);
}

void StateMachineNode::pushState(AIState* state)
{
	if (_stateStack.size() > 0)
		_stateStack.top()->onExit();

	state->setStateMachine(this);
	_stateStack.push(state);
	state->onEnter();
}