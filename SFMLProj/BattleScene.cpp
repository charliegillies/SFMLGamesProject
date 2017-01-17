#include "BattleScene.h"
#include "Game.h"
#include "NodeFactory.h"

BattleScene::BattleScene() {}
BattleScene::~BattleScene() {}

void BattleScene::onStart()
{
	_game->addSceneNode(NodeFactory::createBackgroundNode("Sprites//purple.png"));

	_game->addSceneNode(NodeFactory::createAsteroid(10, 10));

	_game->addSceneNode(NodeFactory::createPlayerNode());

	Scene::onStart();
}
