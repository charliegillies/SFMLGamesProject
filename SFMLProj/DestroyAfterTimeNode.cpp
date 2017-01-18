#include "DestroyAfterTimeNode.h"
#include "Game.h"

DestroyAfterTimeNode::DestroyAfterTimeNode(float destroyTime) 
	: _destroyTime(destroyTime) {}

DestroyAfterTimeNode::~DestroyAfterTimeNode() {}

void DestroyAfterTimeNode::update()
{
	// accumulate time until we hit our target
	_accumulatedTime += getGame()->deltaTime();
	// then destroy our parent, skywalker style
	if (_accumulatedTime >= _destroyTime)
		getGame()->removeSceneNode(getParent());
}