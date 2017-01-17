#include "CollisionNode.h"
#include "EventTags.h"
#include "RegisterColliderEvent.h"

string CollisionNode::getNodeTag()
{
	return NodeTag::collision_node;
}

bool CollisionNode::collides(CollisionNode* testNode)
{
	return false; // template
}

void CollisionNode::start()
{
	//todo cleanup required
	RegisterColliderEvent* register_collider = new RegisterColliderEvent(this);
	invokeGlobalEvent(EventTags::registerCollider, register_collider);
}