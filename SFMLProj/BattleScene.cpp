#include "BattleScene.h"
#include "Game.h"
#include "NodeFactory.h"
#include "CanvasNode.h"
#include "PlayerLivesUINode.h"

BattleScene::BattleScene() {}
BattleScene::~BattleScene() {}

void BattleScene::onStart()
{
	_game->addSceneNode(NodeFactory::createBackgroundNode("Sprites//purple.png"));
	_game->addSceneNode(NodeFactory::createAsteroid(100, 100));
	_game->addSceneNode(NodeFactory::createPlayerNode());

	_game->addSceneNode(NodeFactory::createEnemyUfo(250, 250));


	/* PLAYER UI */
	CanvasNode* canvas = new CanvasNode();
	canvas->addChild(new PlayerLivesUINode());
	_game->addSceneNode(canvas);

	Scene::onStart();
}
