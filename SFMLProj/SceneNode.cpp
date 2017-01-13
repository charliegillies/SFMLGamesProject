#include "SceneNode.h"

SceneNode::SceneNode() : _childNodes()
{
	_parent = nullptr;
	_game = nullptr;
}

SceneNode::~SceneNode() {}

void SceneNode::addChild(SceneNode* node)
{
	// add the child & set the parent
	_childNodes.push_back(node);
	node->setParent(this);
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

Game* SceneNode::getGame()
{
	// only the top most node will have a reference to the game
	return (_game == nullptr) ? _parent->getGame() : _game;
}