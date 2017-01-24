#pragma once
#include "SceneNode.h"
#include <stack>
#include "AIState.h"
#include "TransformNode.h"
#include "CollisionNode.h"

class AIState;

/*
	Scene node that is also a state machine for basic AI.
*/
class StateMachineNode : public SceneNode
{
public:
	StateMachineNode(AIState* defaultState);
	~StateMachineNode();

	void start() override;
	void update() override;

	void pushState(AIState* state);

	void createSceneNode(SceneNode* node);

	float getDt();

	// The cached position of this node during the start() phase.
	sf::Vector2f startPosition;

	// The transform of the node, can be nullptr
	TransformNode* nTransform;

	// A cache of the players transform position
	TransformNode* playerTransform;
	
	// The collider of the node, can be nullptr
	CollisionNode* nCollider;

private:
	AIState* defaultState;
	AIState* currentState;
};

