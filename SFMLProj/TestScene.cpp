#include "TestScene.h"
#include "Game.h"

TestScene::TestScene() : sprite() {}

TestScene::~TestScene() {}

void TestScene::onStart()
{
	sf::Texture& txr = _game->getTexture("playerShip1_blue.png");
	sprite.setTexture(txr);
	sprite.setPosition(0, 0);
}

void TestScene::onExit()
{
}

void TestScene::onUpdate()
{
}

void TestScene::onRender()
{
	_game->drawSprite(sprite);
}