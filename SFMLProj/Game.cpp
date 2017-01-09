#include "Game.h"
#include "Scene.h"

Game::Game()
{
	_currentScene = nullptr;
}

Game::~Game() {}

void Game::onStart()
{
}

void Game::onUpdate()
{
}

void Game::onExit()
{
}

void Game::changeScene(Scene* scene)
{
}