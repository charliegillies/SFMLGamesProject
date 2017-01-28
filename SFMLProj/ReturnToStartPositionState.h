#pragma once
#include "AIState.h"

/*
 * Returns the current entity from it's position to the
 * position of it's statemachine 'start position' property.
 */
class ReturnToStartPositionState : public AIState
{
public:
	ReturnToStartPositionState(float speed);
	~ReturnToStartPositionState();

	void onEnter() override;
	void execute() override;
	void onExit() override;

private:
	float speed;
};
