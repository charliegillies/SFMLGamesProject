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
	dir *= speed;
	dir *= stateMachine->getDt();

	stateMachine->nTransform->position += dir;
}

void SteerTowardsPlayerState::onExit() { }
