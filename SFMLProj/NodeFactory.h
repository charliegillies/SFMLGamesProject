#pragma once
#include "SceneNode.h"

/*
	Factory object for handling the creation of SceneNode hierarchies.
*/
class NodeFactory
{
public:
	static SceneNode* createPlayerNode();
};

