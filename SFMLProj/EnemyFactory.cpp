#include "EnemyFactory.h"
#include "SpriteNode.h"
#include "CollisionNode.h"
#include "ProjectileBuilder.h"
#include "ProjectileDataNode.h"
#include "AIState.h"
#include "UfoIdleState.h"
#include "SteerTowardsPlayerState.h"
#include "ShootState.h"
#include "ReturnToStartPositionState.h"
#include "ViewOnPlayerCondition.h"
#include "CanShootCondition.h"
#include "PlayerInDistanceCondition.h"
#include "FixedCondition.h"
#include "InDistanceOfStartCondition.h"
#include "BomberIdleState.h"
#include "BomberExplodeState.h"
#include "PreExplosionState.h"
#include "TimeCountCondition.h"
#include "TwinShootState.h"
#include "HealthNode.h"
#include "ProjectileCollisionListenerNode.h"
#include "DestroyAfterTimeNode.h"

SceneNode* EnemyFactory::createEnemyUfo(int x, int y)
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
	ProjectileBuilder* projectile_builder = new ProjectileBuilder("Sprites//projectiles//laserRed07.png",
		CollisionNode::PLAYER_MASK | CollisionNode::OBSTACLE_MASK, 1.0f, 200.0f, 15, 8);
	projectile_builder->setCreatorPtr(createRedLaserFx2);

	base_node->addChild(new ProjectileDataNode(0.5f, projectile_builder));

	// health & projectile handling 
	base_node->addChild(new HealthNode(100));
	base_node->addChild(new ProjectileCollisionListenerNode());

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

SceneNode* EnemyFactory::createEnemyBomber(int x, int y)
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

SceneNode* EnemyFactory::createEnemyShooter(int x, int y)
{
	SceneNode* base_node = new SceneNode();
	base_node->addChild(new SpriteNode("Sprites//enemies//twin_shooter.png"));

	// Create transform of ufo
	TransformNode* transform = new TransformNode;
	transform->position = sf::Vector2f(x, y);
	transform->origin = sf::Vector2f(51.5f, 42.0f);
	base_node->addChild(transform);

	// Create appropiate collider
	CollisionNode* collider = new CollisionNode(45);
	collider->setFlags(CollisionNode::ENEMY_MASK,
		CollisionNode::PLAYER_MASK | CollisionNode::OBSTACLE_MASK | CollisionNode::PROJECTILE_MASK);
	base_node->addChild(collider);

	// projectile settings for the shooter
	ProjectileBuilder* projectile_builder = new ProjectileBuilder("Sprites//projectiles//laserRed03.png",
		CollisionNode::PLAYER_MASK | CollisionNode::OBSTACLE_MASK, 1.0f, 200.0f, 15, 8);
	projectile_builder->setCreatorPtr(createRedLaserFx1);

	base_node->addChild(new ProjectileDataNode(0.5f, projectile_builder));

	// health & projectile handling 
	base_node->addChild(new HealthNode(100));
	base_node->addChild(new ProjectileCollisionListenerNode());

	// ai settings for UFO
	float sight_range = 100.0f;
	float lose_sight_range = 150.0f;
	float chase_speed = 120.0f;

	// create the ai state & transitions
	AIState* idle_state = new UfoIdleState();
	AIState* steer_state = new SteerTowardsPlayerState(chase_speed);
	AIState* shoot_state = new TwinShootState();
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

SceneNode* EnemyFactory::createProjectileFx(int x, int y, std::string sprite, sf::Vector2f origin, float life_time)
{
	SceneNode* base_node = new SceneNode();
	base_node->addChild(new SpriteNode(sprite));

	// Create transform of ufo
	TransformNode* transform = new TransformNode;
	transform->position = sf::Vector2f(x, y);
	transform->origin = origin;
	base_node->addChild(transform);

	base_node->addChild(new DestroyAfterTimeNode(life_time));

	return base_node;
}

SceneNode* EnemyFactory::createRedLaserFx1(int x, int y)
{
	return createProjectileFx(x, y, "Sprites//projectiles//laserRed08.png", sf::Vector2f(24, 23), 0.1f);
}

SceneNode* EnemyFactory::createRedLaserFx2(int x, int y)
{
	return createProjectileFx(x, y, "Sprites//projectiles//laserRed09.png", sf::Vector2f(24, 23), 0.1f);
}