#include "SceneNode.h"

SceneNode::SceneNode() : _childNodes()
{
	_parent = nullptr;
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

void SceneNode::render(Game* game)
{
	// render all child nodes
	for (auto i = _childNodes.begin(); i != _childNodes.end(); ++i)
		(*i)->render(game);
}

SceneNode* SceneNode::getParent()
{
	return _parent;
}

void SceneNode::setParent(SceneNode* parent)
{
	_parent = parent;
}