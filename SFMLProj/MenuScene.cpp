#include "MenuScene.h"
#include "CanvasNode.h"
#include "Button.h"
#include "TestScene.h"
#include "TextNode.h"
#include "NodeFactory.h"

MenuScene::MenuScene() {}
MenuScene::~MenuScene() {}

void MenuScene::onStart()
{
	_game->addSceneNode(NodeFactory::createBackgroundNode("Sprites//blue.png"));

	SceneNode* canvasNode = new CanvasNode();

	// game start button
	_gameStartBtn = new Button(400, 400, "Start Game",
		"Sprites//ui//buttonBlue.png", 20);
	_gameStartBtn->setTextColor(sf::Color::Black);
	canvasNode->addChild(_gameStartBtn);

	// game exit button
	_exitBtn = new Button(650, 400, "Quit Game",
		"Sprites//ui//buttonRed.png", 20);
	_exitBtn->setTextColor(sf::Color::Black);
	canvasNode->addChild(_exitBtn);

	// sailor text
	TextNode* text_node = new TextNode(360, 150, "Fonts//kenvector_future.ttf",
		"SAILOR", sf::Color::White, 128);
	canvasNode->addChild(text_node);
	_game->addSceneNode(canvasNode);

	Scene::onStart();
}

void MenuScene::onUpdate()
{
	if (_gameStartBtn->pressed())
	{
		_game->changeScene(new BattleScene());
		return;
	}

	if (_exitBtn->pressed())
	{
		_game->exitGame();
		return;
	}

	Scene::onUpdate();
}