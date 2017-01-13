#include "PlayerShipNode.h"
#include "Game.h"
#include "math.h"

void PlayerShipNode::update()
{
	// rotate towards the mouse
	rotateToMouse();

	if (_controlScheme->forwards())
	{
		_transform->position += sf::Vector2<float>(0, -0.5);
	}
	else if (_controlScheme->backwards())
	{
		_transform->position += sf::Vector2<float>(0, 0.5);
	}
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

void PlayerShipNode::rotateToMouse()
{
	// get mouse and ship position
	auto mousePos = getGame()->getCamera()->getWorldMouse();
	auto pos = _transform->position;
	// rotate towards mouse
	auto angle = atan2(mousePos.y - pos.y, mousePos.x - pos.x);
	angle = angle * (180 / 3.14159265358979323846);
	angle += 90; // sprite doesn't face right, quick fix
	_transform->rotation = angle;
}