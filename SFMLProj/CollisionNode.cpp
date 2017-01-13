#include "CollisionNode.h"


CircleColliderNode::CircleColliderNode()
{
}


CircleColliderNode::~CircleColliderNode()
{
}

string CircleColliderNode::getNodeTag()
{
	return NodeTag::collision_node;
}

bool CircleColliderNode::collides(CircleColliderNode* testNode)
{
	return false; // template
}