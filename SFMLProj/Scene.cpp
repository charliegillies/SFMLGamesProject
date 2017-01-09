#include "Scene.h"
#include "Game.h"

void Scene::setGame(Game* game)
{
	this->_game = game;
}

void Scene::changeScene(Scene* scene)
{
	_game->changeScene(scene);
}