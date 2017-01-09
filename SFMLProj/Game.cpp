#include "Game.h"
#include "Scene.h"

Game::Game(Scene* startScene)
{
	_currentScene = startScene;
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
}