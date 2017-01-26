#pragma once
#include "SceneNode.h"
#include <SFML/System/Vector2.hpp>
#include "CollisionNode.h"

typedef Delegate2<int, int, SceneNode*> objCreatorPtr;

/*
	Builder utility for building projectile scene node objects.
*/
class ProjectileBuilder
{
public:
	ProjectileBuilder(string texture_path, flag colFlag, float lifeTime, float speed, float dmg, float radius, sf::Vector2f origin);

	~ProjectileBuilder();

	// Builds a projectile scene node.
	SceneNode* build(sf::Vector2f position, sf::Vector2f direction, float rot);

	void setCreatorPtr(objCreatorPtr creatorPtr);

private:
	string txr_fp;
	float destroy_time;
	float speed;
	float radius;
	float dmg;
	sf::Vector2f origin;
	flag collision_flag;

	objCreatorPtr _creatorPtr;
};