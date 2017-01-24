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
}

void ReturnToStartPositionState::onExit() { }