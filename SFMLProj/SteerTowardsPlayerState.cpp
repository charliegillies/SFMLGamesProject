#include "SteerTowardsPlayerState.h"
#include "Utils.h"

SteerTowardsPlayerState::SteerTowardsPlayerState(float speed)
	: speed(speed) {}

SteerTowardsPlayerState::~SteerTowardsPlayerState() {}

void SteerTowardsPlayerState::onEnter() { }

void SteerTowardsPlayerState::execute()
{
	sf::Vector2f dir = (stateMachine->playerTransform->position - stateMachine->nTransform->position);
	dir = Utils::normalize(dir);

	sf::Vector2f velocity = dir * speed;
	velocity *= stateMachine->getDt();

	stateMachine->nTransform->position += velocity;

	// Rotate (sprite faces top, so add 90deg)
	stateMachine->nTransform->rotation = 
		Utils::calcAngle(stateMachine->playerTransform->position, 
		stateMachine->nTransform->position) + 90.0f;
}

void SteerTowardsPlayerState::onExit() { }