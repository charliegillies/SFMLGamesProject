#include "PlayerShipNode.h"
#include "Game.h"
#include "math.h"
#include "EventTags.h"
#include "PlayerLostLifeEvent.h"
#include "NodeFactory.h"
#include <iostream>

void PlayerShipNode::update()
{
	// also handles rotation
	sf::Vector2f dir = handleMovement();

	// create a projectile
	if (_controlScheme->fired())
	{
		getGame()->addSceneNode(NodeFactory::createBasicProjectile(
			_transform->position, dir, 480.0f));

		std::cout << "player shot!" << endl;
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


	// Send out 'player lost life' event
	invokeGlobalEvent(EventTags::playerLostLife, new PlayerLostLifeEvent(3));
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

	sf::Vector2f s = mousePos - pos;
	return normalize(s);
}

sf::Vector2f PlayerShipNode::handleMovement()
{
	const float speed = 240.0f;

	// rotate towards the mouse
	sf::Vector2f direction = rotateToMouse();
	sf::Vector2f velocity(0, 0);

	if (_controlScheme->forwards())
		velocity = direction*speed;
	else if (_controlScheme->backwards())
	{
		velocity = direction*(speed / 2);
		velocity = -velocity;
	}

	velocity *= getGame()->deltaTime();
	_transform->position += velocity;

	return direction;
}

sf::Vector2f PlayerShipNode::normalize(sf::Vector2f source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}