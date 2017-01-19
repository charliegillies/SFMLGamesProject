#pragma once
#include "BaseEvent.h"

/*
	Simple event that lets people know that they have been damaged
	by a projectile. This is easily extendable to add more behaviour later.
*/
class ProjectileCollisionEvent : public BaseEvent 
{
public:
	ProjectileCollisionEvent(float dmg) : damageOnHit(dmg) {}
	~ProjectileCollisionEvent() {}

	float damageOnHit;
};

