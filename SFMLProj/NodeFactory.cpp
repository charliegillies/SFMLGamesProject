#include "NodeFactory.h"
#include "TransformNode.h"
#include "SpriteNode.h"
#include "PlayerShipNode.h"
#include "CameraTrackingNode.h"
#include "BackgroundNode.h"
#include "RotationNode.h"
#include "VelocityNode.h"
#include "CollisionNode.h"

SceneNode* NodeFactory::createPlayerNode()
{
	string fp = "Sprites//playerShip1_blue.png";

	SceneNode* base_node = new SceneNode();
	base_node->addChild(new SpriteNode(fp));

	TransformNode* transform_node = new TransformNode();
	transform_node->position = sf::Vector2<float>(100, 100);
	transform_node->origin = sf::Vector2<float>(50, 37);
	base_node->addChild(transform_node);

	base_node->addChild(new PlayerShipNode());
	base_node->addChild(new CameraTrackingNode(0, 0));

	// collider will be static
	base_node->addChild(new CollisionNode(true, 48));

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

	// collider will be static
	base_node->addChild(new CollisionNode(true, 48));

	return base_node;
}

SceneNode* NodeFactory::createEnemyUfo(int x, int y)
{
	SceneNode* base_node = new SceneNode();
	base_node->addChild(new SpriteNode("Sprites//enemies//ufoRed.png"));

	TransformNode* transform = new TransformNode;
	transform->position = sf::Vector2f(x, y);
	base_node->addChild(transform);

	base_node->addChild(new CollisionNode(false, 45));

	return base_node;
}

SceneNode* NodeFactory::createBasicProjectile(sf::Vector2f position, sf::Vector2f direction, float speed, float rot)
{
	SceneNode* base_node = new SceneNode();
	base_node->addChild(new SpriteNode("Sprites//laserBlue03.png"));

	TransformNode* transform_node = new TransformNode();
	transform_node->position = position;
	transform_node->origin = sf::Vector2f(4, 18);
	transform_node->rotation = rot;

	base_node->addChild(transform_node);
	base_node->addChild(new VelocityNode(speed, direction));
	return base_node;
}