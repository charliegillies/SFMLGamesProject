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

void Scene::initializeWaiting()
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
}

void Scene::destroyNodes()
{
	while (!_destroyNodes.empty())
	{
		SceneNode* destroy_node = _destroyNodes.front();
		_destroyNodes.pop();

		// search for the node to destroy, erase it
		for (auto i = _sceneNodes.begin(); i != _sceneNodes.end(); ++i)
		{
			if (destroy_node != (*i)) continue;

			_sceneNodes.erase(i);
			break;
		}
	}
}

void Scene::onUpdate()
{
	initializeWaiting();
	destroyNodes();

	// update all child nodes
	for (auto i = _sceneNodes.begin(); i != _sceneNodes.end(); ++i)
	{
		SceneNode* node = (*i);

		// skip if the node has been removed during this frame
		if (node->waitingRemoval()) continue;

		node->update();
	}
}

void Scene::onRender()
{
	// render all child nodes
	for (auto i = _sceneNodes.begin(); i != _sceneNodes.end(); ++i)
	{
		SceneNode* node = (*i);

		// skip if the node has been removed during this frame
		if (node->waitingRemoval()) continue;

		node->render();
	}
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

void Scene::removeSceneNode(SceneNode* node)
{
	// only the top hierarchy node can be removed, ensure it has no parent
	assert(node->getParent() == nullptr);

	// inform the node that we're removing it from the hiearchy
	node->remove();
	// now put the node into the queue for removal on the next update
	_destroyNodes.push(node);
}

EventSystem* Scene::getEventSystem()
{
	return _eventSystem;
}

void Scene::changeScene(Scene* scene)
{
	_game->changeScene(scene);
}