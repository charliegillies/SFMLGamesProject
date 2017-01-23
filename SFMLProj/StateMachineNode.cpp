#include "StateMachineNode.h"

StateMachineNode::StateMachineNode(AIState* defaultState) : 
	nTransform(nullptr), nCollider(nullptr), _stateStack()
{
	if (defaultState != nullptr)
		_stateStack.push(defaultState);
}

StateMachineNode::~StateMachineNode() {}

void StateMachineNode::start()
{
	// We want to cache some common nodes here so the
	// states can access them without needing to find them again and again
	nTransform = static_cast<TransformNode*>(getParent()->getNode(NodeTag::transform_node));
	nCollider = static_cast<CollisionNode*>	(getParent()->getNode(NodeTag::collision_node));

	SceneNode* playerNode = getGame()->searchForNode("player");
	playerTransform = static_cast<TransformNode*>(playerNode->getNode(NodeTag::transform_node));

	if (_stateStack.size() > 0)
	{
		// get and remove stack element 0
		AIState* state = _stateStack.top();
		_stateStack.pop();

		// now push it, this configures the state properly
		// as it cannot be configured inside of the constructor
		// due to correct execution order.
		pushState(state);
	}
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

	// now check if we can transition out..
	for (auto i = state->transitions.begin(); i != state->transitions.end(); ++i)
	{
		StateTransition* transition = (*i);

		if (transition->conditionMet(this))
		{
			pushState(transition->getNextState());
			break;
		}
	}

	// if we're complete..
	//if (state->isComplete())
	//{
	//	// exit this state
	//	state->onExit();
	//	// remove it from the stack
	//	_stateStack.pop();

	//	// if there are other states in the stack, enter it
	//	if (!_stateStack.empty())
	//		_stateStack.top()->onEnter();
	//}
}

void StateMachineNode::pushState(AIState* state)
{
	if (_stateStack.size() > 0)
		_stateStack.top()->onExit();

	state->setStateMachine(this);
	_stateStack.push(state);
	state->onEnter();
}

float StateMachineNode::getDt()
{
	return getGame()->deltaTime();
}