#include "TestScene.h"
#include "Game.h"

TestScene::TestScene() : sprite() {}

TestScene::~TestScene() {}

void TestScene::onStart()
{
	sprite.setTexture(_game->loadTexture("playerShip1_blue.png"));
	sprite.setColor(sf::Color(255, 255, 255, 255));
	sprite.setPosition(0, 0);
}

void TestScene::onExit()
{
}

void TestScene::onUpdate()
{
	_game->drawSprite(sprite);
}