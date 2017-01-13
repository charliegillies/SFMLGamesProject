#include "NodeFactory.h"
#include "TransformNode.h"
#include "SpriteNode.h"
#include "PlayerShipNode.h"
#include "CameraTrackingNode.h"
#include "BackgroundNode.h"

SceneNode* NodeFactory::createPlayerNode()
{
	string fp = "playerShip1_blue.png";

	SceneNode* base_node = new SceneNode();
	base_node->addChild(new SpriteNode(fp));

	TransformNode* transform_node = new TransformNode();
	transform_node->origin = sf::Vector2<float>(50, 37);
	base_node->addChild(transform_node);

	base_node->addChild(new PlayerShipNode());
	base_node->addChild(new CameraTrackingNode(0, 0));

	return base_node;
}

SceneNode* NodeFactory::createBackgroundNode()
{
	SceneNode* base_node = new SceneNode();
	base_node->addChild(new BackgroundNode());
	base_node->addChild(new TransformNode());
	return base_node;
}

SceneNode* NodeFactory::createAsteroid(int x, int y)
{
	SceneNode* base_node = new SceneNode();
	base_node->addChild(new SpriteNode("meteor_brown.png"));

	TransformNode* node = new TransformNode();
	node->position = sf::Vector2f(x, y);

	base_node->addChild(node);
	return base_node;
}