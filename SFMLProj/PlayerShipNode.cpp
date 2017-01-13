#include "PlayerShipNode.h"
#include "Game.h"
#include "math.h"
#include <iostream>

void PlayerShipNode::update()
{
	// look towards mouse
	auto mousePos = getGame()->getCamera()->getWorldMouse();
	auto pos = _transform->position;

	_transform->rotation += 0.2;

	cout << mousePos.x << " " << mousePos.y << " " << _transform->rotation << endl;

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