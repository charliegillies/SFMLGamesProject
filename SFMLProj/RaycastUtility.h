#pragma once
#include <vector>
#include "CollisionNode.h"

/*
	A simple raycast data structure, with information about
	where the raycast started and ended, if it hit anything
	and what collision node it hit, if any.
*/
struct Raycast
{
	sf::Vector2f start;
	sf::Vector2f end;
	bool hit;
	CollisionNode* collider;
};

/*
	Simple helper utility for raycasting.
*/
class RaycastUtility
{
public:
	RaycastUtility(std::vector<CollisionNode*>& colliders)
		: _colliders(colliders) {}
	~RaycastUtility() {}

private:
	std::vector<CollisionNode*>& _colliders;
};

