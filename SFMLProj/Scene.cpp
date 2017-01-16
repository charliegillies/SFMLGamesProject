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
	int size = _waitingNodes.size();
	for (int i = 0; i < size; i++)
	{
		// get & initialise the node for event subscription
		SceneNode* node = _waitingNodes.front();
		node->subscribeEvents();

		// first really hacky fix so far
		// remove it from the list so we get the next node..
		// but add it again for the next loop initialisation
		_waitingNodes.pop();
		_waitingNodes.push(node);
	}

	for (int i = 0; i < size; i++)
	{
		// get & initialise the node for start()
		SceneNode* node = _waitingNodes.front();
		node->start();

		// add the scene node to the array
		_sceneNodes.push_back(node);
		// remove the node from the queue
		_waitingNodes.pop();
	}

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
	// check if the node shouldn't be added until the next frame
	if (_started)
	{
		_waitingNodes.push(node);
		node->subscribeEvents();
		node->start();
	}
	else // or if it should go immediately into the current node set
		_sceneNodes.push_back(node);
}

EventSystem* Scene::getEventSystem()
{
	return _eventSystem;
}

void Scene::changeScene(Scene* scene)
{
	_game->changeScene(scene);
}