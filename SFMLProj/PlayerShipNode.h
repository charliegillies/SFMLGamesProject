#pragma once
#include "SceneNode.h"
#include "ControlScheme.h"
#include "TransformNode.h"
#include "CollisionNode.h"
#include "RaycastUtility.h"
#include "ProjectileBuilder.h"
#include "PowerUpNode.h"

class PlayerShipNode : public SceneNode
{
public:
	PlayerShipNode() : SceneNode(), _remainingLives(max_lives), _shieldSprite()
	{
		primary_proj_builder = new ProjectileBuilder("Sprites//laserBlue03.png", 
			CollisionNode::ENEMY_MASK | CollisionNode::OBSTACLE_MASK, 2.5f, 400.0f, 15, 8);

		secondary_proj_builder = new ProjectileBuilder("Sprites//missile_1.png",
			CollisionNode::ENEMY_MASK | CollisionNode::OBSTACLE_MASK, 2.5f, 600.0f, 15, 8);
	}

	~PlayerShipNode() {}

	void update() override;
	void start() override;
	void subscribeEvents() override;
	void render() override;
	
private:
	void onCollide(BaseEvent* e);
	void onProjectileCollide(BaseEvent* e);
	void applyPowerup(PowerUpNode* power_up);
	sf::Vector2f getMouseTarget();
	void shootPrimary(sf::Vector2f direction);
	void shootSecondary(sf::Vector2f direction);
	void applyMovement();
	void applyRotation();

	void onLifeChanged();

	// projectile builders
	ProjectileBuilder* primary_proj_builder;
	ProjectileBuilder* secondary_proj_builder;

	// mouse & rotation movement
	sf::Vector2f _mouseTargetRotation;
	sf::Vector2f _mouseLerpRot;

	// collision
	sf::Vector2f _lastMovement;

	// bounds
	sf::Vector2f _topLeftMovementBound;
	sf::Vector2f _botRightMovementBound;

	// the remaining lives
	int _remainingLives;
	static const int max_lives = 3;

	// speed modifier
	float _speedPickupTime;
	// shield modifier
	float _shieldPickupTime;
	sf::Sprite _shieldSprite;

	CollisionNode* _collision;
	ControlScheme* _controlScheme;
	TransformNode* _transform;
};

