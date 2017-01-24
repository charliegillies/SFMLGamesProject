#pragma once
#include "SceneNode.h"
#include "ControlScheme.h"
#include "TransformNode.h"
#include "CollisionNode.h"
#include "RaycastUtility.h"
#include "ProjectileBuilder.h"

class PlayerShipNode : public SceneNode
{
public:
	PlayerShipNode() : SceneNode(), _remainingLives(3)
	{
		proj_builder = new ProjectileBuilder("Sprites//laserBlue03.png", 
			CollisionNode::ENEMY_MASK | CollisionNode::OBSTACLE_MASK, 2.5f, 400.0f, 15, 8);
	}

	~PlayerShipNode() {}

	void update() override;
	void start() override;
	void subscribeEvents() override;
	
private:
	void onCollide(BaseEvent* e);
	void onProjectileCollide(BaseEvent* e);

	ProjectileBuilder* proj_builder;

	Raycast cast;
	sf::Vector2f _mouseTargetRotation;
	sf::Vector2f _mouseLerpRot;

	sf::Vector2f _lastMovement;

	sf::Vector2f _topLeftMovementBound;
	sf::Vector2f _botRightMovementBound;

	sf::Vector2f getMouseTarget();
	void applyMovement();
	void applyRotation();

	void shoot(sf::Vector2f direction);

	int _remainingLives;

	CollisionNode* _collision;
	ControlScheme* _controlScheme;
	TransformNode* _transform;
};

