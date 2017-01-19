#pragma once
#include "SceneNode.h"
#include "ControlScheme.h"
#include "TransformNode.h"
#include "CollisionNode.h"
#include "RaycastUtility.h"

class PlayerShipNode : public SceneNode
{
public:
	PlayerShipNode() : SceneNode() {}
	~PlayerShipNode() {}

	void update() override;
	void start() override;
	void render() override;

private:
	void onCollide(BaseEvent* e);

	Raycast cast;
	sf::Vector2f _mouseTargetRotation;
	sf::Vector2f _mouseLerpRot;

	sf::Vector2f _topLeftMovementBound;
	sf::Vector2f _botRightMovementBound;

	sf::Vector2f getMouseTarget();
	void applyMovement();
	void applyRotation();

	void shoot(sf::Vector2f direction);

	CollisionNode* _collision;
	ControlScheme* _controlScheme;
	TransformNode* _transform;
};

