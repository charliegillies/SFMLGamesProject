#pragma once
#include "SceneNode.h"

/*
	Factory object for handling the creation of SceneNode hierarchies.
*/
class NodeFactory
{
public:
	static SceneNode* createPlayerNode();

	static SceneNode* createBackgroundNode(string filepath);

	static SceneNode* createAsteroid(int x, int y);

	static SceneNode* createSonicExplosion(int x, int y);

	static SceneNode* createPixelExplosion(int x, int y);

	static SceneNode* createHealthPickup(int x, int y);

	static SceneNode* createSpeedPickup(int x, int y);

	static SceneNode* createShieldPickup(int x, int y);
};