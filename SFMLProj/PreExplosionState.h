#pragma once
#include "AIState.h"
class PreExplosionState : public AIState
{
public:
	PreExplosionState();
	~PreExplosionState();

	void onEnter() override;
	void execute() override;
	void onExit() override;
};

