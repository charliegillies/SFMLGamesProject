#pragma once
#include "SceneNode.h"
#include <stack>
#include "AIState.h"

class AIBrain;
class AIState;

/*
	Scene node that is also a state machine for basic AI.
*/
class StateMachineNode : public SceneNode
{
public:
	StateMachineNode(AIBrain* brain);
	~StateMachineNode();

	void start() override;
	void update() override;

	// Not to be confused with 'ask brian'
	// Brian will get annoyed if you ask him questions a lot
	void askBrain();

	void pushState(AIState* state);

private:
	AIBrain* _brain;
	stack<AIState*> _stateStack;
};

