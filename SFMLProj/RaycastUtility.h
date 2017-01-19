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
	RaycastUtility(std::vector<CollisionNode*>& colliders, Game* game)
		: _colliders(colliders), game(game) {}
	~RaycastUtility() {}

	Raycast cast(sf::Vector2f start, sf::Vector2f dir, float range);

	void drawCast(Raycast raycast);
private:
	std::vector<CollisionNode*> getPotentialColliders(sf::Vector2f start, float range);

	sf::RectangleShape rectangle;
	Game* game;
	std::vector<CollisionNode*>& _colliders;
};

