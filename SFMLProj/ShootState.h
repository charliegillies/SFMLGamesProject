#pragma once
#include "AIState.h"
#include "ProjectileDataNode.h"

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

private:
	ProjectileDataNode* projectile_data_node;
};
