#include "TestScene.h"
#include "Game.h"
#include "SpriteNode.h"

TestScene::TestScene() {}
TestScene::~TestScene() {}

void TestScene::onStart()
{
	std::string fp = "playerShip1_blue.png";

	// create a basic empty node, with a sprite node and transform child
	SceneNode* base_node = new SceneNode();
	base_node->addChild(new SpriteNode(fp));
	base_node->addChild(new TransformNode());
	_game->addSceneNode(base_node);

	Scene::onStart();
}
