#include "RaycastUtility.h"
#include "Utils.h"
#include <iostream>

Raycast RaycastUtility::cast(sf::Vector2f start, sf::Vector2f dir, float range, flag searchCategory)
{
	Raycast ray;
	ray.start = start;
	ray.end = start + (dir * range);
	ray.hit = false;
	ray.collider = nullptr;

	// get all in range potential colliders
	auto potentials = getPotentialColliders(searchCategory, start, range);
	// early exit if no potentials are found
	if (potentials.size() == 0)
		return ray;

	// check for actual collisions with the potentials
	vector<Raycast> colliding;

	for (auto i = potentials.begin(); i != potentials.end(); ++i)
	{
		CollisionNode* potential = (*i);
		Raycast cast = potential->testRaycast(ray);

		if (cast.hit)
			colliding.push_back(cast);
	}

	Raycast closest_hit = ray;
	float closest_dst = 100000;

	// find the closest hit
	for (auto i = colliding.begin(); i != colliding.end(); ++i)
	{
		Raycast& cast = (*i);

		float dst = Utils::distance(start, cast.intersect_1);
		
		if (dst < closest_dst)
		{
			closest_dst = dst;
			closest_hit = cast;
		}
	}

	return closest_hit;
}

void RaycastUtility::drawCast(Raycast raycast)
{
	// set the position, rotation & size of the raycast
	shape_ray_line.setPosition(raycast.start);
	shape_ray_line.setRotation(Utils::calcAngle(raycast.start, raycast.end) + 90);
	shape_ray_line.setSize(sf::Vector2f(4, Utils::distance(raycast.start, raycast.end)));
	shape_ray_line.setFillColor(raycast.hit ? sf::Color::Green : sf::Color::White);
	game->draw(shape_ray_line);

	shape_ray_int_1.setPosition(raycast.start);
	shape_ray_int_2.setPosition(raycast.end);
	game->draw(shape_ray_int_1);
	game->draw(shape_ray_int_2);

	if (raycast.hit)
	{
		shape_ray_int_1.setPosition(raycast.intersect_1);
		shape_ray_int_2.setPosition(raycast.intersect_2);
		game->draw(shape_ray_int_1);
		game->draw(shape_ray_int_2);
	}
}

void RaycastUtility::setGame(Game* game)
{
	this->game = game;
}

std::vector<CollisionNode*> RaycastUtility::getPotentialColliders(flag searchCategory, sf::Vector2f start, float range)
{
	std::vector<CollisionNode*> nodes_in_range;

	for (auto i = _colliders.begin(); i != _colliders.end(); ++i)
	{
		auto testCollider = (*i);

		// check bitwise operation to see if this is a compatible collider
		if (testCollider->test_flag)
			if ((testCollider->categoryBits & searchCategory) == 0)
				continue;

		// calc range
		float x = testCollider->getX();
		float y = testCollider->getY();

		// calc distance between these ray start pos and test pos
		float dst = Utils::distance(start, sf::Vector2f(x, y));
		
		// app width just incase
		if (dst < (range + (testCollider->getWidth()/2)))
			nodes_in_range.push_back(testCollider);
	}

	return nodes_in_range;
}