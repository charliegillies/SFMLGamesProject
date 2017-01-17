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

	// Collision map settings
	static const int NUM_CELLS_X = 40;
	static const int NUM_CELLS_Y = 40;
	static const int CELL_SIZE = 50;

	void subscribeEvents() override;
	void onColliderRegister(BaseEvent* e);

	void update() override;

private:
	std::vector<CollisionNode*> _allColliders;
	CollisionMap _collisionMap;
};