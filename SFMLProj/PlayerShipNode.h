#pragma once
#include "SceneNode.h"
#include "ControlScheme.h"
#include "TransformNode.h"
#include "CollisionNode.h"
#include "RaycastUtility.h"
#include "ProjectileBuilder.h"
#include "PowerUpNode.h"
#include "NodeFactory.h"
#include "HealthNode.h"
#include "ProjectileDataNode.h"

class PlayerShipNode : public SceneNode
{
public:
	PlayerShipNode() : SceneNode(), _shieldSprite(), _shieldUp(false)
	{
		auto primary_proj_builder = new ProjectileBuilder("Sprites//projectiles//laserBlue03.png", 
			CollisionNode::ENEMY_MASK | CollisionNode::OBSTACLE_MASK, 0.6f, 800, 15, 8);
		primary_proj_builder->setCreatorPtr(NodeFactory::createProjectileBlueFx);

		auto secondary_proj_builder = new ProjectileBuilder("Sprites//projectiles//missile_1.png",
			CollisionNode::ENEMY_MASK | CollisionNode::OBSTACLE_MASK, 0.8f, 1000, 15, 8);
		secondary_proj_builder->setCreatorPtr(NodeFactory::createPixelExplosion);
	
		primaryFire = new ProjectileDataNode(0.25f, primary_proj_builder);
		secondaryFire = new ProjectileDataNode(1.2f, secondary_proj_builder);
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

	void broadcastStatusChange();

	bool isShieldUp();

	// health node, has max hp & current hp
	HealthNode* _hpNode;
	// shield information
	HealthNode* _shieldHpNode;
	bool _shieldUp;
	sf::Sprite _shieldSprite;

	// projectile builders
	ProjectileDataNode* primaryFire;
	ProjectileDataNode* secondaryFire;

	// mouse & rotation movement
	sf::Vector2f _mouseTargetRotation;
	sf::Vector2f _mouseLerpRot;

	// collision
	sf::Vector2f _lastMovement;

	// bounds
	sf::Vector2f _topLeftMovementBound;
	sf::Vector2f _botRightMovementBound;

	// speed modifier
	float _speedPickupTime;

	CollisionNode* _collision;
	ControlScheme* _controlScheme;
	TransformNode* _transform;
};

