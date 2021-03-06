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
#include "AudioNode.h"

class PlayerShipNode : public SceneNode
{
public:
	PlayerShipNode() : SceneNode(), _shieldUp(false), _shieldSprite()
	{
		auto primary_proj_builder = new ProjectileBuilder("Sprites//projectiles//laserBlue03.png", 
			CollisionNode::ENEMY_MASK | CollisionNode::OBSTACLE_MASK, 0.6f, 800, 25, 8, sf::Vector2f(4.5f, 8.0f));
		primary_proj_builder->setCreatorPtr(NodeFactory::createProjectileBlueFx);

		auto secondary_proj_builder = new ProjectileBuilder("Sprites//projectiles//missile_1.png",
			CollisionNode::ENEMY_MASK | CollisionNode::OBSTACLE_MASK, 0.8f, 1000, 45, 8, sf::Vector2f(9.5f, 20.0f));
		secondary_proj_builder->setCreatorPtr(NodeFactory::createPixelExplosion);
		secondary_proj_builder->audio_fp = "Sfx//missile_hit.wav";
		
		primaryFire = new ProjectileDataNode(0.25f, primary_proj_builder);
		secondaryFire = new ProjectileDataNode(1.2f, secondary_proj_builder);

		primaryAudioNode = new AudioNode(AudioPlayMode::PLAY_ON_TRIGGER, "Sfx//laser9w.wav");
		secondaryAudioNode = new AudioNode(AudioPlayMode::PLAY_ON_TRIGGER, "Sfx//fireball.wav");
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
	AudioNode* primaryAudioNode;
	AudioNode* secondaryAudioNode;

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

