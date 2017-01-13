#include "CameraTrackingNode.h"
#include "Game.h"

void CameraTrackingNode::start()
{
	_camera = getGame()->getCamera();

	// try and get a transform node
	SceneNode* node;
	if (getParent() != nullptr)
	{
		node = getParent()->getNode(NodeTag::transform_node);

		// attempt cast
		if (node != nullptr)
			_transform = static_cast<TransformNode*>(node);
	}

	_camera->setCenter(_transform->position.x + _xOffset, _transform->position.y + _yOffset);
}

void CameraTrackingNode::update()
{
	_camera->setCenter(_transform->position.x + _xOffset, _transform->position.y + _yOffset);
}