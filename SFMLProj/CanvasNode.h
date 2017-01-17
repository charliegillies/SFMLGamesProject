#pragma once
#include "SceneNode.h"

/*
	A canvas node is the super-parent to all UI scene nodes.
	All UI scene nodes need to have a CanvasNode as an direct
	or indirect parent node.
*/
class CanvasNode : public SceneNode
{
public:
	CanvasNode();
	~CanvasNode();

	void update() override;
	void render() override;
};

