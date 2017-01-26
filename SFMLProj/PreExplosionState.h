#pragma once
#include "AIState.h"

/*
	State that runs before the bomber explodes.
*/
class PreExplosionState : public AIState
{
public:
	PreExplosionState();
	~PreExplosionState();

	void onEnter() override;
	void execute() override;
	void onExit() override;

private:
	sf::Vector2f _startScale;
};

