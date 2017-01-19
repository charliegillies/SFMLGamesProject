#include "RaycastUtility.h"
#include "Utils.h"

Raycast RaycastUtility::cast(sf::Vector2f start, sf::Vector2f dir, float range)
{
	Raycast ray;
	ray.start = start;
	ray.end = start + (dir * range);



	return ray;
}

void RaycastUtility::drawCast(Raycast raycast)
{
	// set the position, rotation & size of the raycast
	rectangle.setPosition(raycast.start);
	rectangle.setRotation(Utils::calcAngle(raycast.start, raycast.end));
	rectangle.setSize(sf::Vector2f(4, Utils::distance(raycast.start, raycast.end)));

	game->draw(rectangle);
}
