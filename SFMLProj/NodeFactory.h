#pragma once
#include "SceneNode.h"
#include <SFML/System/Vector2.hpp>

/*
	Factory object for handling the creation of SceneNode hierarchies.
*/
class NodeFactory
{
public:
	static SceneNode* createPlayerNode();

	static SceneNode* createBackgroundNode(string filepath);

	static SceneNode* createAsteroid(int x, int y);

	static SceneNode* createEnemyUfo(int x, int y);

	static SceneNode* createShipProjectile(sf::Vector2f position, sf::Vector2f direction, float speed, float rot);
};