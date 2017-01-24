#pragma once
#include "SceneNode.h"
#include <SFML/System/Vector2.hpp>
#include "CollisionNode.h"

/*
	Builder utility for building projectile scene node objects.
*/
class ProjectileBuilder
{
public:
	ProjectileBuilder(string texture_path, flag colFlag, float lifeTime, float speed, float dmg, float radius);

	~ProjectileBuilder();

	// Builds a projectile scene node.
	SceneNode* build(sf::Vector2f position, sf::Vector2f direction, float rot);

private:
	string txr_fp;
	float destroy_time;
	float speed;
	float radius;
	float dmg;
	flag collision_flag;

};