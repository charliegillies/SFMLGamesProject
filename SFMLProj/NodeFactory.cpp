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
#include "BomberIdleState.h"
#include "BomberExplodeState.h"
#include "AnimatedSpriteNode.h"
#include "MultiCondition.h"
#include "TimeCountCondition.h"
#include "PreExplosionState.h"

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
	transform->origin = sf::Vector2f(45.5f, 45.5f);
	base_node->addChild(transform);

	// Create appropiate collider
	CollisionNode* collider = new CollisionNode(45);
	collider->setFlags(CollisionNode::ENEMY_MASK, 
		CollisionNode::PLAYER_MASK | CollisionNode::OBSTACLE_MASK | CollisionNode::PROJECTILE_MASK);
	base_node->addChild(collider);

	// projectile settings for the ufo
	ProjectileBuilder* projectile_builder = new ProjectileBuilder("Sprites//projectiles//laserBlue03.png", 
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

SceneNode* NodeFactory::createEnemyBomber(int x, int y)
{
	SceneNode* base_node = new SceneNode();
	base_node->addChild(new SpriteNode("Sprites//enemies//bomber.png"));

	// Create transform of ufo
	TransformNode* transform = new TransformNode;
	transform->position = sf::Vector2f(x, y);
	transform->origin = sf::Vector2f(51.5f, 42);
	base_node->addChild(transform);

	// Create appropiate collider
	CollisionNode* collider = new CollisionNode(45, sf::Vector2f(8, 0));
	collider->setFlags(CollisionNode::ENEMY_MASK,
		CollisionNode::PLAYER_MASK | CollisionNode::OBSTACLE_MASK | CollisionNode::PROJECTILE_MASK);
	base_node->addChild(collider);

	// projectile settings for the ufo
	ProjectileBuilder* projectile_builder = new ProjectileBuilder("Sprites//projectiles//laserBlue03.png",
		CollisionNode::PLAYER_MASK | CollisionNode::OBSTACLE_MASK, 1.0f, 200.0f, 15, 8);

	base_node->addChild(new ProjectileDataNode(0.5f, projectile_builder));

	// ai settings for UFO
	float chase_speed = 250.0f;
	float charge_speed = chase_speed * 1.4f;

	float sight_range = 400.0f;
	float lose_sight_range = 450.0f;
	float charge_range = 150.0f;
	float bomb_range = 100.0f;

	// create the ai state & transitions
	AIState* idle_state = new BomberIdleState();
	AIState* chase_state = new SteerTowardsPlayerState(chase_speed);
	AIState* charge_state = new SteerTowardsPlayerState(charge_speed);
	AIState* explode_state = new BomberExplodeState(bomb_range);
	AIState* return_state = new ReturnToStartPositionState(chase_speed / 1.5f);
	AIState* pre_explode_state = new PreExplosionState();

	// a1, IDLE -> (SEE PLAYER?) -> CHASE/STEER
	idle_state->addTransition(new ViewOnPlayerCondition(sight_range), chase_state);

	// a2, CHASE -> (SEE PLAYER IN BOMB RANGE?) -> CHARGE
	chase_state->addTransition(new ViewOnPlayerCondition(charge_range), charge_state);
	
	// a4, CHASE -> (LOST SIGHT OF PLAYER?) -> RETURN
	auto lost_sight_condition = new ViewOnPlayerCondition(lose_sight_range);
	lost_sight_condition->toggleViewAsInverse();
	chase_state->addTransition(lost_sight_condition, return_state);

	// a3, CHARGE -> (IN BOMB DISTANCE?) -> BEGIN TO EXPLODE
	charge_state->addTransition(new PlayerInDistanceCondition(bomb_range + 5.0f), pre_explode_state);

	// a5, BEGIN TO EXPLODE -> (TIME PASSED?) -> EXPLODE
	pre_explode_state->addTransition(new TimeCountCondition(0.5f), explode_state);

	// create the state machine
	base_node->addChild(new StateMachineNode(idle_state));

	return base_node;
}

SceneNode* NodeFactory::createSonicExplosion(int x, int y)
{
	SceneNode* base_node = new SceneNode();
	
	TransformNode* transform_node = new TransformNode();
	transform_node->position = sf::Vector2f(x, y);
	base_node->addChild(transform_node);

	// create animation
	AnimatedSpriteNode* animation = new AnimatedSpriteNode(
		"Sprites//animations//sonic_explosion.png", 0.04f, ANIM_DELETE_SELF);

	// add animation frames
	animation
		->addFrame(284, 0, 152, 150)
		->addFrame(192, 284, 190, 190)
		->addFrame(0, 0, 284, 284)
		->addFrame(531, 140, 120, 124)
		->addFrame(525, 301, 133, 134)
		->addFrame(436, 0, 138, 140)
		->addFrame(382, 301, 143, 144)
		->addFrame(382, 150, 149, 151);
	
	base_node->addChild(animation);

	return base_node;
}

SceneNode* NodeFactory::createPixelExplosion(int x, int y)
{
	SceneNode* base_node = new SceneNode();

	TransformNode* transform_node = new TransformNode();
	transform_node->position = sf::Vector2f(x, y);
	transform_node->scale = sf::Vector2f(2, 2);
	base_node->addChild(transform_node);

	// create animation
	AnimatedSpriteNode* animation = new AnimatedSpriteNode(
		"Sprites//animations//pixel_explosion.png", 0.06f, ANIM_DELETE_SELF);

	// add animation frames
	animation
		->addFrame(96, 182, 96, 91)
		->addFrame(96, 91, 96, 91)
		->addFrame(96, 0, 96, 91)
		->addFrame(96, 273, 96, 91)
		->addFrame(0, 273, 96, 91)
		->addFrame(0, 182, 96, 91)
		->addFrame(0, 0, 96, 91)
		->addFrame(0, 364, 96, 91);

	base_node->addChild(animation);

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