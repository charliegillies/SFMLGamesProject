#pragma once
#include "BaseEvent.h"
#include "Scene.h"

class CollisionNode;

/*
	Event is invoked when the entity collides with another entity.
	
	This is invoked by the CollisionNode, after it's told it has collided.
	A lot of different behaviours will want to listen for this event.
*/
class CollisionEvent : public BaseEvent
{
public:
	// the collider that belongs to us
	CollisionNode* collider_a;
	// the collider that we hit
	CollisionNode* collider_b;

	CollisionEvent() {}
	~CollisionEvent() {}
};