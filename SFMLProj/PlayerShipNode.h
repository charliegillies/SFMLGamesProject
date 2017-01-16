#pragma once
#include "SceneNode.h"
#include "ControlScheme.h"
#include "TransformNode.h"

class PlayerShipNode : public SceneNode
{
public:
	PlayerShipNode() : SceneNode() {}
	~PlayerShipNode() {}

	void update() override;
	void start() override;

private:
	sf::Vector2f rotateToMouse();
	sf::Vector2f handleMovement();

	ControlScheme* _controlScheme;
	TransformNode* _transform;

	sf::Vector2f normalize(sf::Vector2f source);
};

