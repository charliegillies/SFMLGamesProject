#include "Game.h"
#include "Scene.h"

Game::Game(Scene* scene, sf::RenderWindow* window)
{
	changeScene(scene);
	this->_window = window;
}

Game::~Game() {}

void Game::onStart()
{
	if (_currentScene != nullptr)
		_currentScene->onStart();
}

void Game::onUpdate()
{
	if (_currentScene != nullptr)
		_currentScene->onUpdate();
}

void Game::onExit()
{
	if (_currentScene != nullptr)
		_currentScene->onExit();
}

void Game::changeScene(Scene* scene)
{
	scene->setGame(this);
	_currentScene = scene;
}

void Game::drawSprite(sf::Sprite sprite)
{
	_window->draw(sprite);
}

sf::Texture Game::loadTexture(std::string fp)
{
	sf::Texture texture;
	//todo fix asap
	static const std::string prefix = "Content\\";
	texture.loadFromFile(prefix + fp);
	return texture;
}