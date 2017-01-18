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
	void update() override;

private:
	void onColliderRegister(BaseEvent* e);

	CollisionMap _collisionMap;
	std::vector<CollisionNode*> _allColliders;
};