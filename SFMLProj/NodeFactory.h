#pragma once
#include "SceneNode.h"
#include <SFML/System/Vector2.hpp>

/*
	Factory object for handling the creation of SceneNode hierarchies.
*/
class NodeFactory
{
public:
	static SceneNode* createPlayerNode(float x, float y);

	static SceneNode* createBackgroundNode(string filepath);

	static SceneNode* createAsteroid(int x, int y);

	static SceneNode* createSonicExplosion(int x, int y);

	static SceneNode* createPixelExplosion(int x, int y);

	static SceneNode* createHealthPickup(int x, int y);

	static SceneNode* createSpeedPickup(int x, int y);

	static SceneNode* createShieldPickup(int x, int y);

	static SceneNode* createProjectileFx(int x, int y, string sprite, sf::Vector2f origin, float life_time);
	static SceneNode* createProjectileBlueFx(int x, int y);
};