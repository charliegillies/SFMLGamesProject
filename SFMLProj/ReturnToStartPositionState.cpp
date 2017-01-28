#include "ReturnToStartPositionState.h"
#include "Utils.h"

ReturnToStartPositionState::ReturnToStartPositionState(float speed)
	: speed(speed) { }

ReturnToStartPositionState::~ReturnToStartPositionState() { }

void ReturnToStartPositionState::onEnter() { }

void ReturnToStartPositionState::execute()
{
	sf::Vector2f dir = (stateMachine->startPosition - stateMachine->nTransform->position);

	dir = Utils::normalize(dir);
	dir *= speed;
	dir *= stateMachine->getDt();

	stateMachine->nTransform->position += dir;

	// Rotate (sprite faces top, so add 90deg)
	stateMachine->nTransform->rotation = 
		Utils::calcAngle(stateMachine->startPosition,
		stateMachine->nTransform->position) + 90.0f;
}

void ReturnToStartPositionState::onExit() { }