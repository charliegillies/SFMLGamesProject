#include "MenuScene.h"
#include "CanvasNode.h"
#include "Button.h"
#include "BattleScene.h"
#include "TextNode.h"
#include "NodeFactory.h"
#include "IntroScene.h"

MenuScene::MenuScene() {}
MenuScene::~MenuScene() {}

void MenuScene::onStart()
{
	_game->addSceneNode(NodeFactory::createBackgroundNode("Sprites//backgrounds//blue.png"));

	SceneNode* canvasNode = new CanvasNode();

	// game start button
	_gameStartBtn = new Button(400, 400, 
		"Sprites//ui//buttonBlue.png", new TextNode(0, 0, 
		"Fonts//kenvector_future.ttf", "Start Game", sf::Color::Black, 20));
	canvasNode->addChild(_gameStartBtn);

	// game exit button
	_exitBtn = new Button(650, 400,
		"Sprites//ui//buttonRed.png", new TextNode(0, 0,
		"Fonts//kenvector_future.ttf", "Quit Game", sf::Color::Black, 20));
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
		_game->changeScene(new IntroScene());
		return;
	}

	if (_exitBtn->pressed())
	{
		_game->exitGame();
		return;
	}

	Scene::onUpdate();
}