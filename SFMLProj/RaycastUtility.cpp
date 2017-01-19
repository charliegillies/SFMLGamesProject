#include "RaycastUtility.h"
#include "Utils.h"

Raycast RaycastUtility::cast(sf::Vector2f start, sf::Vector2f dir, float range)
{
	Raycast ray;
	ray.start = start;
	ray.end = start + (dir * range);
	ray.hit = false;
	ray.collider = nullptr;

	// get all in range potential colliders
	auto colliders_in_range = getPotentialColliders(start, range);
	
	// now sort 


	return ray;
}

void RaycastUtility::drawCast(Raycast raycast)
{
	// set the position, rotation & size of the raycast
	rectangle.setPosition(raycast.start);
	rectangle.setRotation(Utils::calcAngle(raycast.start, raycast.end));
	rectangle.setSize(sf::Vector2f(4, Utils::distance(raycast.start, raycast.end)));

	// draw red if the ray hit, else draw white
	rectangle.setFillColor(raycast.hit ? sf::Color::Red : sf::Color::White);

	game->draw(rectangle);
}

std::vector<CollisionNode*> RaycastUtility::getPotentialColliders(sf::Vector2f start, float range)
{
	std::vector<CollisionNode*> nodes_in_range;

	for (auto i = _colliders.begin(); i != _colliders.end(); ++i)
	{
		auto testCollider = (*i);

		// calc range
		float x = testCollider->getX();
		float y = testCollider->getY();

		float dst = Utils::distance(start, sf::Vector2f(x, y));
		
		if (dst < range)
			nodes_in_range.push_back(testCollider);
	}

	return nodes_in_range;
}