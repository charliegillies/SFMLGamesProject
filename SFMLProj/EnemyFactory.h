#pragma once
#include <string>
#include <SFML/System/Vector2.hpp>

class SceneNode;

/*
	Factory object for processing data.	
*/
class EnemyFactory
{
public:
	static SceneNode* createEnemyUfo(int x, int y);

	static SceneNode* createEnemyBomber(int x, int y);

	static SceneNode* createEnemyShooter(int x, int y);

private:
	static SceneNode* createRedLaserFx1(int x, int y);
	static SceneNode* createRedLaserFx2(int x, int y);
};