#pragma once
#include "AIState.h"
#include "ProjectileDataNode.h"
#include "AudioNode.h"

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
	virtual void shoot(TransformNode* transform, sf::Vector2f dir);
	void onExit() override;

protected:
	ProjectileDataNode* projectile_data_node;
	AudioNode* audio_node;
	sf::Transform sf_transform;
};
