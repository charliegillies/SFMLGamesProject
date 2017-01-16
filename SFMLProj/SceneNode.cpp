#include "SceneNode.h"
#include "Game.h"

SceneNode::SceneNode() : _childNodes()
{
	_parent = nullptr;
	_game = nullptr;
}

SceneNode::~SceneNode() {}

SceneNode* SceneNode::addChild(SceneNode* node)
{
	// add the child & set the parent
	_childNodes.push_back(node);
	node->setParent(this);
	return this;
}

void SceneNode::subscribeEvents()
{
	// subscribe for all child nodes
	for (auto i = _childNodes.begin(); i != _childNodes.end(); ++i)
		(*i)->subscribeEvents();
}

void SceneNode::start()
{
	// start all child nodes
	for (auto i = _childNodes.begin(); i != _childNodes.end(); ++i)
		(*i)->start();
}

void SceneNode::update()
{
	// update all child nodes
	for (auto i = _childNodes.begin(); i != _childNodes.end(); ++i)
		(*i)->update();
}

void SceneNode::render()
{
	// render all child nodes
	for (auto i = _childNodes.begin(); i != _childNodes.end(); ++i)
		(*i)->render();
}

SceneNode* SceneNode::getParent()
{
	return _parent;
}

void SceneNode::setParent(SceneNode* parent)
{
	_parent = parent;
}

void SceneNode::setGame(Game* game)
{
	_game = game;
}

string SceneNode::getNodeTag()
{
	return NodeTag::empty_node;
}

SceneNode* SceneNode::getNode(string tag)
{
	// navigate through all the nodes to find the matching tag
	for (auto i = _childNodes.begin(); i != _childNodes.end(); ++i)
	{
		string nodeTag = (*i)->getNodeTag();
		
		if (tag == nodeTag)
			return (*i);
	}
	
	return nullptr;
}

EventReceiver* SceneNode::addGlobalEventReceiver(const string id, void(* receiver)(BaseEvent*))
{
	return getGame()->getEventSystem()->addReceiver(id, receiver);
}

void SceneNode::invokeGlobalEvent(const string id, BaseEvent* param)
{
	getGame()->getEventSystem()->invokeEvent(id, param);
}

Game* SceneNode::getGame()
{
	// only the top most node will have a reference to the game
	return (_game == nullptr) ? _parent->getGame() : _game;
}