#include "TestScene.h"
#include "Game.h"
#include "NodeFactory.h"

TestScene::TestScene() {}
TestScene::~TestScene() {}

void TestScene::onStart()
{
	_game->addSceneNode(NodeFactory::createBackgroundNode());

	_game->addSceneNode(NodeFactory::createAsteroid(10, 10));

	_game->addSceneNode(NodeFactory::createPlayerNode());


	Scene::onStart();
}
