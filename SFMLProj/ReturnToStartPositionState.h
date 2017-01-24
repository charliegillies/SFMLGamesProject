#pragma once
#include "AIState.h"

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
