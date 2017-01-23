#pragma once
#include "AIState.h"

/*
	Steers towards the player.
*/
class SteerTowardsPlayerState : public AIState 
{
public:
	SteerTowardsPlayerState(float speed);
	~SteerTowardsPlayerState();

	void onEnter() override;
	void execute() override;
	void onExit() override;

private:
	float speed;
};