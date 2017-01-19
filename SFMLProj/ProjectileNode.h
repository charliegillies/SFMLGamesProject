#pragma once
#include "SceneNode.h"

/*
	Simple behavioural node that listens for a local collision event.

	On colliding, notifies the other node we collided with that they
	hit a projectile and then deletes self from the hierarchy.

	Ensure that the collision flags are properly set up, as this 
	will notify anyone that it collides with - uncaring about their behaviour.
*/
class ProjectileNode : public SceneNode
{
public:
	explicit ProjectileNode(float damageOnHit) : dmg(damageOnHit) {}
	~ProjectileNode() {}

	void subscribeEvents() override;

private:
	float dmg;
	void onCollide(BaseEvent* event);
};