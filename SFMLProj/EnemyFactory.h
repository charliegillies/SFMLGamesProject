#pragma once

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
};