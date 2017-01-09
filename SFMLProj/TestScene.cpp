#include "TestScene.h"
#include "SFML/Graphics.hpp"

TestScene::TestScene()
{
}

sf::Texture loadTexture(std::string fp)
{
	sf::Texture texture;
	//todo fix asap
	static const std::string prefix = "Content\\";
	texture.loadFromFile(prefix + fp);
	return texture;
}

TestScene::~TestScene()
{
}

void TestScene::onStart()
{
	sf::Texture texture = loadTexture("playerShip1_blue.png");
}

void TestScene::onExit()
{
}

void TestScene::onUpdate()
{
}