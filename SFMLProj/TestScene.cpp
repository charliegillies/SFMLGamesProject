#include "TestScene.h"
#include "Game.h"
#include "NodeFactory.h"
#include "TextRenderNode.h"

TestScene::TestScene() {}
TestScene::~TestScene() {}

void TestScene::onStart()
{
	_game->addSceneNode(NodeFactory::createBackgroundNode());

	_game->addSceneNode(NodeFactory::createAsteroid(10, 10));

	_game->addSceneNode(NodeFactory::createPlayerNode());

	auto testNode = new SceneNode;
	testNode->addChild(new TextRenderNode("Fonts//kenvector_future.ttf", "Hello, World."));
	_game->addSceneNode(testNode);

	Scene::onStart();
}
