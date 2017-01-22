#pragma once
#include "AIState.h"

/*
	Base idle state of the UFO.
*/
class UfoIdleState : public AIState
{
public:
	UfoIdleState();
	~UfoIdleState();

	void onEnter() override;
	void execute() override;
	void onExit() override;
};