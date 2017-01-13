#include "Scene.h"
#include "Game.h"

void Scene::onStart() {}

void Scene::onExit() {}

void Scene::onUpdate()
{
	// update all child nodes
	for (auto i = _sceneNodes.begin(); i != _sceneNodes.end(); ++i)
		(*i)->update();
}

void Scene::onRender()
{
	// render all child nodes
	for (auto i = _sceneNodes.begin(); i != _sceneNodes.end(); ++i)
		(*i)->render();
}

void Scene::setGame(Game* game)
{
	this->_game = game;
}

void Scene::addSceneNode(SceneNode* node)
{
	_sceneNodes.push_back(node);
}

void Scene::changeScene(Scene* scene)
{
	_game->changeScene(scene);
}