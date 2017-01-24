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
	// get direction..
	sf::Vector2f direction = (stateMachine->playerTransform->position - 
		stateMachine->nTransform->position);
	direction = Utils::normalize(direction);

	Raycast cast = stateMachine->nCollider->raycast(stateMachine->playerTransform->position,
		direction, range, CollisionNode::ALL_MASKS);

	return cast.hit && cast.collider->getParent()->getName() == "player";
}