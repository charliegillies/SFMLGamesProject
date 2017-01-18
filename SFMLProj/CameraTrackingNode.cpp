#include "CameraTrackingNode.h"
#include "Game.h"
#include "CollisionMap.h"
#include "Utils.h"

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

	_camera->setCenter(_transform->position.x, _transform->position.y);

	// set the camera bounds
	sf::Vector2f camera_half_size = _camera->getSize();
	camera_half_size = camera_half_size / 2.0f;
	float world_width = CollisionMap::width * CollisionMap::cellSize;
	float world_height = CollisionMap::height * CollisionMap::cellSize;
	top_left = camera_half_size;
	bot_right = sf::Vector2f(world_width, world_height) - camera_half_size;

	// align the camera
	sf::Vector2f target = getTargetPosition();
	_camera->setCenter(target.x, target.y);
}

void CameraTrackingNode::update()
{
	sf::Vector2f target = getTargetPosition();
	_camera->setCenter(target.x, target.y);
}

sf::Vector2f CameraTrackingNode::getTargetPosition()
{
	// ensure that the camera is in the world bounds
	sf::Vector2f position = _transform->position;
	position.x = Utils::clamp(position.x, top_left.x, bot_right.x);
	position.y = Utils::clamp(position.y, top_left.y, bot_right.y);
	return position;
}