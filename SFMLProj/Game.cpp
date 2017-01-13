#include "Game.h"
#include "Scene.h"

Game::Game(Scene* scene, sf::RenderWindow* window)
{
	changeScene(scene);
	this->_window = window;
	this->textureLoader = new TextureLoader();
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

void Game::onRender()
{
	if (_currentScene != nullptr)
		_currentScene->onRender();
}

void Game::changeScene(Scene* scene)
{
	scene->setGame(this);
	_currentScene = scene;
}

sf::Texture& Game::getTexture(const std::string fp)
{
	return textureLoader->get(fp);
}

void Game::addSceneNode(SceneNode* node)
{
	if (_currentScene == nullptr) return;

	_currentScene->addSceneNode(node);
	_currentScene->setGame(this);
}

void Game::drawSprite(sf::Sprite sprite)
{
	_window->draw(sprite);
}