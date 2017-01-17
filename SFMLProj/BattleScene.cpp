#include "BattleScene.h"
#include "Game.h"
#include "NodeFactory.h"
#include "CanvasNode.h"
#include "PlayerLivesUINode.h"
#include "CollisionHandler.h"

BattleScene::BattleScene() {}
BattleScene::~BattleScene() {}

void BattleScene::onStart()
{
	// load standard game background
	_game->addSceneNode(NodeFactory::createBackgroundNode("Sprites//purple.png"));
	
	// we're going to either load or generate our asteroids and enemies
	_game->addSceneNode(NodeFactory::createAsteroid(100, 100));
	_game->addSceneNode(NodeFactory::createEnemyUfo(250, 250));

	// add the collision handler node
	_game->addSceneNode(new CollisionHandler());

	// create the player node
	_game->addSceneNode(NodeFactory::createPlayerNode());

	/* PLAYER UI */
	CanvasNode* canvas = new CanvasNode();
	canvas->addChild(new PlayerLivesUINode());
	_game->addSceneNode(canvas);

	Scene::onStart();
}
