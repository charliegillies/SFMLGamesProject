#include "NodeFactory.h"
#include "TransformNode.h"
#include "SpriteNode.h"
#include "PlayerShipNode.h"
#include "CameraTrackingNode.h"
#include "BackgroundNode.h"
#include "RotationNode.h"
#include "VelocityNode.h"
#include "CollisionNode.h"
#include "DestroyAfterTimeNode.h"

SceneNode* NodeFactory::createPlayerNode()
{
	string fp = "Sprites//playerShip1_blue.png";

	SceneNode* base_node = new SceneNode();
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
		CollisionNode::ENEMY_MASK | CollisionNode::OBSTACLE_MASK | CollisionNode::PROJECTILE );
	
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
	base_node->addChild(new SpriteNode("Sprites//enemies//ufoRed.png"));

	TransformNode* transform = new TransformNode;
	transform->position = sf::Vector2f(x, y);
	transform->origin = sf::Vector2f(40.5f, 40.5f);
	base_node->addChild(transform);

	CollisionNode* collider = new CollisionNode(45);
	collider->setFlags(CollisionNode::ENEMY_MASK, 
		CollisionNode::PLAYER_MASK | CollisionNode::OBSTACLE_MASK | CollisionNode::PROJECTILE);

	base_node->addChild(collider);

	return base_node;
}

SceneNode* NodeFactory::createShipProjectile(sf::Vector2f position, sf::Vector2f direction, float speed, float rot)
{
	SceneNode* base_node = new SceneNode();
	base_node->addChild(new SpriteNode("Sprites//laserBlue03.png"));

	TransformNode* transform_node = new TransformNode();
	transform_node->position = position;
	transform_node->origin = sf::Vector2f(4, 18);
	transform_node->rotation = rot;
	base_node->addChild(transform_node);

	// destroy after 2.5 seconds
	base_node->addChild(new DestroyAfterTimeNode(2.5f));

	// setup collider
	CollisionNode* collider = new CollisionNode(8);
	collider->setFlags(CollisionNode::PROJECTILE, CollisionNode::ENEMY_MASK | CollisionNode::OBSTACLE_MASK);
	base_node->addChild(collider);

	base_node->addChild(new VelocityNode(speed, direction));

	return base_node;
}