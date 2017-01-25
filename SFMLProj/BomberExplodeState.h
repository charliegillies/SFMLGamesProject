#pragma once
#include "AIState.h"

/*
	State which is unique to the bomber ai.
	Explodes and damages everything in a distance.
*/
class BomberExplodeState : public AIState
{
public:
	explicit BomberExplodeState(float range);
	~BomberExplodeState();

	void onEnter() override;
	void execute() override;
	void onExit() override;

private:
	float range;
};

