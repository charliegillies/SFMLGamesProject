#include "NodeFactory.h"
#include "TransformNode.h"
#include "SpriteNode.h"
#include "PlayerShipNode.h"
#include "CameraTrackingNode.h"

SceneNode* NodeFactory::createPlayerNode()
{
	string fp = "playerShip1_blue.png";

	SceneNode* base_node = new SceneNode();
	base_node->addChild(new SpriteNode(fp));
	base_node->addChild(new TransformNode());
	base_node->addChild(new PlayerShipNode());
	base_node->addChild(new CameraTrackingNode(50, 37));

	return base_node;
}