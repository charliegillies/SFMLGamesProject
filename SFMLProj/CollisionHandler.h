#pragma once
#include <vector>

#include "SceneNode.h"
#include "CollisionNode.h"
#include "CollisionMap.h"

/*
	Handles collision inside of the world space for entities
	that send out a RegisterCollider event.
*/
class CollisionHandler : public SceneNode
{
public:
	CollisionHandler();
	~CollisionHandler();

	void subscribeEvents() override;
	void onColliderRegister(BaseEvent* e);

	void update() override;

private:
	std::vector<CollisionNode*> _allColliders;
	CollisionMap _collisionMap;
};