#pragma once
#include "BaseEvent.h"
#include "CollisionNode.h"
#include "RaycastUtility.h"

/*
	Event that allows the collision handler to listen for
	the creation of certain colliders inside of the scene graph.
*/
class RegisterColliderEvent : public BaseEvent
{
public:
	CollisionNode* collider;
	RaycastUtility* rayUtility;

	RegisterColliderEvent(CollisionNode* collider)
	{
		this->collider = collider;
	}

	~RegisterColliderEvent() {};
};

