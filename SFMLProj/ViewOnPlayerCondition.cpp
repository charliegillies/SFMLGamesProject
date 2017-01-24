#include "ViewOnPlayerCondition.h"
#include <SFML/System/Vector2.hpp>
#include "StateMachineNode.h"
#include "Utils.h"
#include "RaycastUtility.h"

ViewOnPlayerCondition::ViewOnPlayerCondition(float range)
	: range(range) { }

ViewOnPlayerCondition::~ViewOnPlayerCondition() { }

bool ViewOnPlayerCondition::conditionMet(StateMachineNode* stateMachine)
{
	// get direction of the player for the raycast
	sf::Vector2f direction = (stateMachine->playerTransform->position - 
		stateMachine->nTransform->position);
	direction = Utils::normalize(direction);

	Raycast cast = stateMachine->nCollider->raycast(stateMachine->nTransform->position,
		direction, range, CollisionNode::ALL_MASKS);

	// if the cast hit - and it was the player that we hit..
	return cast.hit && cast.collider->getParent()->getName() == "player";
}