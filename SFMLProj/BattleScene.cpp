#include "BattleScene.h"
#include "Game.h"
#include "NodeFactory.h"
#include "CanvasNode.h"
#include "PlayerLivesUINode.h"
#include "CollisionHandler.h"
#include "EnemyFactory.h"
#include "GameStateListener.h"
#include "AudioNode.h"

BattleScene::BattleScene() {}
BattleScene::~BattleScene() {}

void BattleScene::onStart()
{
	// game state listener waits to hear about changes in the world state
	_game->addSceneNode(new GameStateListener());

	// load standard game background
	_game->addSceneNode(NodeFactory::createBackgroundNode("Sprites//backgrounds//purple.png"));
	
	// we're going to either load or generate our asteroids and enemies
	_game->addSceneNode(NodeFactory::createAsteroid(100, 100));
	
	// create dummy test enemies
	_game->addSceneNode(EnemyFactory::createEnemyUfo(600, 600));
	_game->addSceneNode(EnemyFactory::createEnemyBomber(700, 700));
	_game->addSceneNode(EnemyFactory::createEnemyShooter(900, 600));

	// add the collision handler node
	_game->addSceneNode(new CollisionHandler());

	// create the player node
	_game->addSceneNode(NodeFactory::createPlayerNode());

	_game->addSceneNode(NodeFactory::createHealthPickup(1000, 500));
	_game->addSceneNode(NodeFactory::createShieldPickup(800, 500));
	_game->addSceneNode(NodeFactory::createSpeedPickup(1000, 300));

	/* PLAYER UI */
	CanvasNode* canvas = new CanvasNode();
	canvas->addChild(new PlayerLivesUINode());
	_game->addSceneNode(canvas);

	Scene::onStart();
}