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
	void onCollide(BaseEvent* e);

	sf::Vector2f rotateToMouse();
	sf::Vector2f handleMovement();

	void shoot(sf::Vector2f direction);

	ControlScheme* _controlScheme;
	TransformNode* _transform;
};

