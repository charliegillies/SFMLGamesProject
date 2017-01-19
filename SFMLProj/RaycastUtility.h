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
	sf::Vector2f intersect_1;
	sf::Vector2f intersect_2;

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
		: _colliders(colliders), game(game)
	{
		shape_ray_int_1.setFillColor(sf::Color::Black);
		shape_ray_int_1.setRadius(8);
		shape_ray_int_1.setOrigin(4, 4);
		shape_ray_int_1.setOutlineColor(sf::Color::White);
		shape_ray_int_1.setOutlineThickness(1);

		shape_ray_int_2.setFillColor(sf::Color::White);
		shape_ray_int_2.setRadius(8);
		shape_ray_int_2.setOrigin(4, 4);
		shape_ray_int_2.setOutlineColor(sf::Color::Black);
		shape_ray_int_2.setOutlineThickness(1);
	}
	~RaycastUtility() {}

	Raycast cast(sf::Vector2f start, sf::Vector2f dir, float range, flag searchCategory);

	void drawCast(Raycast raycast);
private:
	std::vector<CollisionNode*> getPotentialColliders(flag searchCategory, sf::Vector2f start, float range);

	/* DEBUG SHAPES */
	sf::RectangleShape shape_ray_line;
	sf::CircleShape shape_ray_int_1;
	sf::CircleShape shape_ray_int_2;

	Game* game;
	std::vector<CollisionNode*>& _colliders;
};

