#include "NodeFactory.h"
#include "TransformNode.h"
#include "SpriteNode.h"
#include "PlayerShipNode.h"
#include "CameraTrackingNode.h"
#include "BackgroundNode.h"
#include "RotationNode.h"
#include "CollisionNode.h"
#include "AIState.h"
#include "AnimatedSpriteNode.h"
#include "DestroyAfterTimeNode.h"

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

	base_node->addChild(new HealthNode(200));

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

SceneNode* NodeFactory::createProjectileFx(int x, int y, std::string sprite, sf::Vector2f origin, float life_time)
{
	SceneNode* base_node = new SceneNode();
	base_node->addChild(new SpriteNode(sprite));

	// Create transform of ufo
	TransformNode* transform = new TransformNode;
	transform->position = sf::Vector2f(x, y);
	transform->origin = origin;
	transform->scale = sf::Vector2f(0.5f, 0.5f);
	base_node->addChild(transform);

	base_node->addChild(new DestroyAfterTimeNode(life_time));

	return base_node;
}

SceneNode* NodeFactory::createProjectileBlueFx(int x, int y)
{
	return createProjectileFx(x, y, "Sprites//projectiles//laserBlue09.png", sf::Vector2f(24, 23), 0.1f);
}