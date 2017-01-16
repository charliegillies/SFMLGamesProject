#include "Scene.h"
#include "Game.h"

void Scene::onStart()
{
	// allow all child nodes to set up their events
	for (auto i = _sceneNodes.begin(); i != _sceneNodes.end(); ++i)
		(*i)->subscribeEvents();

	// start all child nodes
	for (auto i = _sceneNodes.begin(); i != _sceneNodes.end(); ++i)
		(*i)->start();

	_started = true;
}

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

	if (_started)
	{
		node->subscribeEvents();
		node->start();
	}
}

EventSystem* Scene::getEventSystem()
{
	return _eventSystem;
}

void Scene::changeScene(Scene* scene)
{
	_game->changeScene(scene);
}