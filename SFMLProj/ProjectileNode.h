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
	explicit ProjectileNode(float damageOnHit) : dmg(damageOnHit), audio_hit_fp(""), onDeathCreateFunc(nullptr) {}
	~ProjectileNode() {}

	void subscribeEvents() override;

	// On the death/collision of this projectile,
	// this method will be invoked and the returning object
	// will be added to the scene hierarchy.
	Delegate2<int, int, SceneNode*> onDeathCreateFunc;

	string audio_hit_fp;

private:
	float dmg;
	void onCollide(BaseEvent* event);
};