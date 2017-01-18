#include "VelocityNode.h"
#include "Game.h"

void VelocityNode::update()
{
	// calculate vector
	sf::Vector2f velocity = _direction;
	velocity *= _speed;
	velocity *= getGame()->deltaTime();

	// apply velocity onto position
	_transform->position += velocity;
}

void VelocityNode::start()
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