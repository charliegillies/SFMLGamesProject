#pragma once
#include "SceneNode.h"
#include <stack>
#include "AIState.h"

class AIState;

/*
	Scene node that is also a state machine for basic AI.
*/
class StateMachineNode : public SceneNode
{
public:
	StateMachineNode();
	~StateMachineNode();

	void start() override;
	void update() override;

	void pushState(AIState* state);

private:
	stack<AIState*> _stateStack;
};

