#include "PreExplosionState.h"

PreExplosionState::PreExplosionState() { } 
PreExplosionState::~PreExplosionState() { }

void PreExplosionState::onEnter()
{
	_startScale = stateMachine->nTransform->scale;
}

void PreExplosionState::execute()
{
	float scale_theta = stateMachine->getAppTime() / 0.075f;
	float scale_dst = sin(scale_theta);

	stateMachine->nTransform->scale = _startScale + sf::Vector2f(0.075f, 0.075f) * scale_dst;
}

void PreExplosionState::onExit()
{
}