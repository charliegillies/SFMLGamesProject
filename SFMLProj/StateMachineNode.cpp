#include "StateMachineNode.h"

StateMachineNode::StateMachineNode(AIState* defaultState) 
	: nTransform(nullptr), nCollider(nullptr), defaultState(defaultState), currentState(nullptr) {}

StateMachineNode::~StateMachineNode() {}

void StateMachineNode::start()
{
	// We want to cache some common nodes here so the
	// states can access them without needing to find them again and again
	nTransform = static_cast<TransformNode*>(getParent()->getNode(NodeTag::transform_node));
	nCollider = static_cast<CollisionNode*>	(getParent()->getNode(NodeTag::collision_node));

	// cache start position
	startPosition = nTransform->position;

	// find the player, get its transform node
	SceneNode* playerNode = getGame()->searchForNode("player");
	playerTransform = static_cast<TransformNode*>(playerNode->getNode(NodeTag::transform_node));

	// initialise default state
	pushState(defaultState);
}

void StateMachineNode::update()
{
	// get current state, execute it
	auto state = currentState;
	state->execute();

	// now check if we can transition out..
	for (auto i = state->transitions.begin(); i != state->transitions.end(); ++i)
	{
		StateTransition* transition = (*i);

		// check if we met the condition
		bool conditionMet = transition->conditionMet(this);
		// now check if we need to inverse it
		if (transition->viewAsInverse)
			conditionMet = !conditionMet;

		if (conditionMet)
		{
			pushState(transition->getNextState());
			break;
		}
	}
}

void StateMachineNode::pushState(AIState* state)
{
	if (currentState != nullptr)
		currentState->onExit();

	state->setStateMachine(this);
	currentState = state;
	state->onEnter();
}

float StateMachineNode::getDt()
{
	return getGame()->deltaTime();
}