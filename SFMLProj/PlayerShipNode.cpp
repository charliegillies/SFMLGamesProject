#include "PlayerShipNode.h"
#include "Game.h"
#include "math.h"

void PlayerShipNode::update()
{
	const float speed = 8.0f;

	// rotate towards the mouse
	sf::Vector2f direction = rotateToMouse();
	sf::Vector2f velocity(0, 0);

	if (_controlScheme->forwards())
	{
		velocity = direction*speed;
		velocity = -velocity;
	}
	else if (_controlScheme->backwards())
		velocity = direction*speed;

	velocity *= getGame()->deltaTime();

	_transform->position += velocity;
}

void PlayerShipNode::start()
{
	_controlScheme = getGame()->getControlScheme();

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

sf::Vector2f PlayerShipNode::rotateToMouse()
{
	// get mouse and ship position
	auto mousePos = getGame()->getCamera()->getWorldMouse();
	auto pos = _transform->position;
	// rotate towards mouse
	auto angle = atan2(mousePos.y - pos.y, mousePos.x - pos.x);
	angle = angle * (180 / 3.14159265358979323846);
	angle += 90; // sprite doesn't face right, quick fix
	_transform->rotation = angle;

	return mousePos - pos;
}