#include "NodeFactory.h"
#include "TransformNode.h"
#include "SpriteNode.h"
#include "PlayerShipNode.h"
#include "CameraTrackingNode.h"
#include "BackgroundNode.h"
#include "RotationNode.h"
#include "CollisionNode.h"
#include "AIState.h"
#include "UfoIdleState.h"
#include "PlayerInDistanceCondition.h"
#include "SteerTowardsPlayerState.h"
#include "ViewOnPlayerCondition.h"
#include "ShootState.h"
#include "ReturnToStartPositionState.h"
#include "CanShootCondition.h"
#include "FixedCondition.h"
#include "InDistanceOfStartCondition.h"
#include "ProjectileDataNode.h"

SceneNode* NodeFactory::createPlayerNode()
{
	string fp = "Sprites//player//ship.png";

	SceneNode* base_node = new SceneNode();
	base_node->setName("player");
	base_node->addChild(new SpriteNode(fp));

	TransformNode* transform_node = new TransformNode();
	transform_node->position = sf::Vector2<float>(250, 100);
	transform_node->origin = sf::Vector2<float>(49.5f, 37.5f);
	base_node->addChild(transform_node);

	base_node->addChild(new PlayerShipNode());
	base_node->addChild(new CameraTrackingNode());

	// collider will be static
	CollisionNode* collider = new CollisionNode(40, sf::Vector2f(9, -6));

	// i am the player, and i can collide with the enemy and obstacles.
	collider->setFlags(CollisionNode::PLAYER_MASK, 
		CollisionNode::ENEMY_MASK | CollisionNode::OBSTACLE_MASK 
		| CollisionNode::PROJECTILE_MASK | CollisionNode::PICKUP_MASK );
	
	base_node->addChild(collider);

	return base_node;
}

SceneNode* NodeFactory::createBackgroundNode(string filepath)
{
	SceneNode* base_node = new SceneNode();
	base_node->addChild(new BackgroundNode(filepath));
	base_node->addChild(new TransformNode());
	return base_node;
}

SceneNode* NodeFactory::createAsteroid(int x, int y)
{
	SceneNode* base_node = new SceneNode();
	base_node->addChild(new SpriteNode("Sprites//meteor_brown.png"));

	TransformNode* transform_node = new TransformNode();
	// lazy hard coding, but origin is sprite size / 2
	transform_node->origin = sf::Vector2f(49, 48);
	transform_node->position = sf::Vector2f(x, y);

	base_node->addChild(new RotationNode(60));
	base_node->addChild(transform_node);

	CollisionNode* collider = new CollisionNode(48);
	collider->setFlags(CollisionNode::OBSTACLE_MASK, CollisionNode::ALL_MASKS);

	base_node->addChild(collider);

	return base_node;
}

SceneNode* NodeFactory::createEnemyUfo(int x, int y)
{
	SceneNode* base_node = new SceneNode();
	base_node->addChild(new SpriteNode("Sprites//enemies//ufo.png"));

	// Create transform of ufo
	TransformNode* transform = new TransformNode;
	transform->position = sf::Vector2f(x, y);
	transform->origin = sf::Vector2f(40.5f, 40.5f);
	base_node->addChild(transform);

	// Create appropiate collider
	CollisionNode* collider = new CollisionNode(45);
	collider->setFlags(CollisionNode::ENEMY_MASK, 
		CollisionNode::PLAYER_MASK | CollisionNode::OBSTACLE_MASK | CollisionNode::PROJECTILE_MASK);
	base_node->addChild(collider);

	// projectile settings for the ufo
	ProjectileBuilder* projectile_builder = new ProjectileBuilder("Sprites//laserBlue03.png", 
		CollisionNode::PLAYER_MASK | CollisionNode::OBSTACLE_MASK, 1.0f, 200.0f, 15, 8);

	base_node->addChild(new ProjectileDataNode(0.5f, projectile_builder));

	// ai settings for UFO
	float sight_range = 100.0f;
	float lose_sight_range = 150.0f;
	float chase_speed = 120.0f;

	// create the ai state & transitions
	AIState* idle_state = new UfoIdleState();
	AIState* steer_state = new SteerTowardsPlayerState(chase_speed);
	AIState* shoot_state = new ShootState();
	AIState* return_state = new ReturnToStartPositionState(chase_speed / 1.5f);

	//a1 IDLE -> MOVE TO PLAYER
	idle_state->addTransition(new ViewOnPlayerCondition(sight_range), steer_state);

	//a2 MOVE TO PLAYER -> SHOOT @ PLAYER
	steer_state->addTransition(new CanShootCondition(), shoot_state);
	
	//a4, if distance between us and player is too far, give up and return
	auto outOfRangeCondition = new PlayerInDistanceCondition(lose_sight_range);
	outOfRangeCondition->toggleViewAsInverse();
	steer_state->addTransition(outOfRangeCondition, return_state);

	//a3, GO BACK TO MOVING TO PLAYER
	shoot_state->addTransition(new FixedCondition(true), steer_state);

	//a5, return to idle state from return state
	return_state->addTransition(new InDistanceOfStartCondition(10.0f), idle_state);

	//a6, chase player if they spot it while retreating
	return_state->addTransition(new ViewOnPlayerCondition(sight_range), steer_state);

	// now create the state machine
	base_node->addChild(new StateMachineNode(idle_state));

	return base_node;
}

SceneNode* NodeFactory::createHealthPickup(int x, int y)
{
	SceneNode* base_node = new SceneNode();
	base_node->addChild(new SpriteNode("Sprites//pickups//health.png"));

	TransformNode* transform_node = new TransformNode();
	// lazy hard coding, but origin is sprite size / 2
	transform_node->origin = sf::Vector2f(11, 10.5f);
	transform_node->position = sf::Vector2f(x, y);
	base_node->addChild(transform_node);

	CollisionNode* collider = new CollisionNode(12);
	collider->setFlags(CollisionNode::PICKUP_MASK, CollisionNode::PLAYER_MASK);
	base_node->addChild(collider);

	base_node->addChild(new PowerUpNode(PICKUP_HEALTH));

	return base_node;
}

SceneNode* NodeFactory::createSpeedPickup(int x, int y)
{
	SceneNode* base_node = new SceneNode();
	base_node->addChild(new SpriteNode("Sprites//pickups//speed.png"));

	TransformNode* transform_node = new TransformNode();
	// lazy hard coding, but origin is sprite size / 2
	transform_node->origin = sf::Vector2f(17, 16.5f);
	transform_node->position = sf::Vector2f(x, y);
	base_node->addChild(transform_node);

	CollisionNode* collider = new CollisionNode(17.0f);
	collider->setFlags(CollisionNode::PICKUP_MASK, CollisionNode::PLAYER_MASK);
	base_node->addChild(collider);

	base_node->addChild(new PowerUpNode(PICKUP_SPEED));

	return base_node;
}

SceneNode* NodeFactory::createShieldPickup(int x, int y)
{
	SceneNode* base_node = new SceneNode();
	base_node->addChild(new SpriteNode("Sprites//pickups//shield.png"));

	TransformNode* transform_node = new TransformNode();
	// lazy hard coding, but origin is sprite size / 2
	transform_node->origin = sf::Vector2f(17, 16.5f);
	transform_node->position = sf::Vector2f(x, y);
	base_node->addChild(transform_node);

	CollisionNode* collider = new CollisionNode(17.0f);
	collider->setFlags(CollisionNode::PICKUP_MASK, CollisionNode::PLAYER_MASK);
	base_node->addChild(collider);

	base_node->addChild(new PowerUpNode(PICKUP_SHIELD));

	return base_node;
}