#pragma once
#include <vector>

#include "SceneNode.h"
#include "CollisionNode.h"
#include "CollisionMap.h"
#include <map>

typedef map<string, bool> CheckMap;

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

	void checkPotentialCollisions(CheckMap& map, vector<CollisionNode*>& nodes);

private:
	void onColliderRegister(BaseEvent* e);
	void onColliderUnregister(BaseEvent* e);

	void unregisterWaiting();

	int tests = 0;
	int collisions = 0;

	queue<CollisionNode*> _unregisterQueue;
	vector<CollisionNode*> _allColliders;
	CollisionMap _collisionMap;
};