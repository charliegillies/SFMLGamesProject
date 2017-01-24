#pragma once
#include "AIState.h"

/*
	State that involves shooting towards an enemy.
*/
class ShootState : public AIState
{
public:
	ShootState();
	~ShootState();

	void onEnter() override;
	void execute() override;
	void onExit() override;
};