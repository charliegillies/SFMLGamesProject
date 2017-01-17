#pragma once
#include "BaseEvent.h"
#include "CollisionNode.h"

/*
	Event that allows the collision handler to listen for
	the creation of certain colliders inside of the scene graph.
*/
class RegisterColliderEvent : public BaseEvent
{
public:
	CollisionNode* collider;

	RegisterColliderEvent(CollisionNode* collider)
	{
		this->collider = collider;
	}

	~RegisterColliderEvent() {};
};

