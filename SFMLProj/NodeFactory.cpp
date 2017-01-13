#include "NodeFactory.h"
#include "TransformNode.h"
#include "SpriteNode.h"

SceneNode* NodeFactory::createPlayerNode()
{
	string fp = "playerShip1_blue.png";

	SceneNode* base_node = new SceneNode();
	base_node->addChild(new SpriteNode(fp));
	base_node->addChild(new TransformNode());

	return base_node;
}