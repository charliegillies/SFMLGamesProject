#include "MenuScene.h"
#include "CanvasNode.h"
#include "Button.h"
#include "TestScene.h"
#include "TextNode.h"

MenuScene::MenuScene() {}
MenuScene::~MenuScene() {}

void MenuScene::onStart()
{
	SceneNode* base_node = new CanvasNode();

	// game start button
	_gameStartBtn = new Button(100, 100, "Start Game",
		"Sprites//ui//buttonBlue.png", 20);
	_gameStartBtn->setTextColor(sf::Color::Black);
	base_node->addChild(_gameStartBtn);

	// game exit button
	_exitBtn = new Button(100, 200, "Quit Game",
		"Sprites//ui//buttonRed.png", 20);
	_exitBtn->setTextColor(sf::Color::Black);
	base_node->addChild(_exitBtn);

	base_node->addChild(new TextNode(0, 0, "Fonts//kenvector_future.ttf", 
		"SAILOR", sf::Color::White, 128));


	_game->addSceneNode(base_node);

	Scene::onStart();
}

void MenuScene::onUpdate()
{
	if (_gameStartBtn->pressed())
	{
		_game->changeScene(new TestScene());
		return;
	}

	if (_exitBtn->pressed())
	{
		_game->exitGame();
		return;
	}

	Scene::onUpdate();
}