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
	_game->addSceneNode(NodeFactory::createAsteroid(10, 10));
	_game->addSceneNode(NodeFactory::createPlayerNode());

	/* UI */
	CanvasNode* canvas = new CanvasNode();
	PlayerLivesUINode* playerLivesNode = new PlayerLivesUINode();
	canvas->addChild(playerLivesNode);

	Delegate1<BaseEvent*> e;
	//e.Bind(playerLivesNode)

	_game->addSceneNode(canvas);

	Scene::onStart();
}
