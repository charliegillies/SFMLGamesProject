#pragma once
#include "BaseEvent.h"
#include "Scene.h"

/*
	Event is invoked when the entity collides with another entity.
	
	This is invoked by the CollisionNode, after it's told it has collided.
	A lot of different behaviours will want to listen for this event.
*/
class CollisionEvent : public BaseEvent
{
public:
	// the parent scene node of the collider that we hit.
	SceneNode* collider;

	CollisionEvent() {}
	~CollisionEvent() {}
};