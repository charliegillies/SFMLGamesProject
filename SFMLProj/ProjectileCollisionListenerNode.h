#pragma once
#include "SceneNode.h"
#include "HealthNode.h"

/*
	Listens for the projectile collision event and
	deducts health appropiately from the health node.

	Also destroys the unit when it hits 0 hp.
*/
class ProjectileCollisionListenerNode : public SceneNode
{
public:
	ProjectileCollisionListenerNode();
	~ProjectileCollisionListenerNode();

	void start() override;
	void subscribeEvents() override;

	void onProjectileCollide(BaseEvent* proj_collision);


private:
	HealthNode* hp_node;
};

