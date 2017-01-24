#pragma once
#include "SceneNode.h"
#include "Game.h"
#include "ProjectileBuilder.h"

/*
	Compositite and behavioural class that holds data 
	about the projectiles of the scene node parent and
	helps count down the time between the actors shooting.
*/
class ProjectileDataNode : public SceneNode
{
public:
	const float timeBetweenShots;
	float timeTillNextShot;

	// Build utility for building the projectile.
	ProjectileBuilder* builder;

	ProjectileDataNode(const float timeBetweenShots, ProjectileBuilder* builder) 
		: timeBetweenShots(timeBetweenShots), timeTillNextShot(0), builder(builder) {}
	
	~ProjectileDataNode() {}

	void update() override
	{
		timeTillNextShot -= getGame()->deltaTime();

		if (timeTillNextShot < 0)
			timeTillNextShot = 0;
	}

	// Sets the time to next shot to be equal to the time between shots
	void onShoot()
	{
		timeTillNextShot = timeBetweenShots;
	}

	string getNodeTag() override
	{
		return NodeTag::projectile_data_node;
	}
};
