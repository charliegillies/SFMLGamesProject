#include "RotationNode.h"
#include "Game.h"

RotationNode::RotationNode(float rotPerSecond)
{
	_rotPerSecond = rotPerSecond;
}

RotationNode::~RotationNode() {}

void RotationNode::update()
{
	float rot = _rotPerSecond * getGame()->deltaTime();
	_transform->rotation += rot;
}

void RotationNode::start()
{
	// try and get a transform node
	SceneNode* node;
	if (getParent() != nullptr)
	{
		node = getParent()->getNode(NodeTag::transform_node);

		// attempt cast
		if (node != nullptr)
			_transform = static_cast<TransformNode*>(node);
	}

	// ensure that _transform is not null
	assert(_transform != nullptr);
}