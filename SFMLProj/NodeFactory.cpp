#include "NodeFactory.h"
#include "TransformNode.h"
#include "SpriteNode.h"
#include "PlayerShipNode.h"
#include "CameraTrackingNode.h"
#include "BackgroundNode.h"
#include "RotationNode.h"
#include "VelocityNode.h"

SceneNode* NodeFactory::createPlayerNode()
{
	string fp = "Sprites//playerShip1_blue.png";

	SceneNode* base_node = new SceneNode();
	base_node->addChild(new SpriteNode(fp));

	TransformNode* transform_node = new TransformNode();
	transform_node->origin = sf::Vector2<float>(50, 37);
	base_node->addChild(transform_node);

	base_node->addChild(new PlayerShipNode());
	base_node->addChild(new CameraTrackingNode(0, 0));

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