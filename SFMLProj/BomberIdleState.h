#pragma once
#include "AIState.h"

/*
	Idle state of the bomber. Extended for later functionality.
*/
class BomberIdleState : public AIState 
{
public:
	BomberIdleState();
	~BomberIdleState();
	
	void onEnter() override;
	void execute() override;
	void onExit() override;
};