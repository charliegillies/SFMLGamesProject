#include "TestScene.h"
#include "Game.h"
#include "NodeFactory.h"

TestScene::TestScene() {}
TestScene::~TestScene() {}

void TestScene::onStart()
{
	_game->addSceneNode(NodeFactory::createPlayerNode());

	Scene::onStart();
}
