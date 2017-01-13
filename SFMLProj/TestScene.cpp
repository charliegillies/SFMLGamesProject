#include "TestScene.h"
#include "Game.h"
#include "SpriteNode.h"

TestScene::TestScene() {}
TestScene::~TestScene() {}

void TestScene::onStart()
{
	std::string fp = "playerShip1_blue.png";

	// create a basic empty node, with a sprite node child
	SceneNode* base_node = new SceneNode();
	SceneNode* sprite_node = new SpriteNode(fp);
	base_node->addChild(sprite_node);

	_game->addSceneNode(base_node);

	Scene::onStart();
}
