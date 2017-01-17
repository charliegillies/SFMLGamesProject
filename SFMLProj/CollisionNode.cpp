#include "CollisionNode.h"
#include "EventTags.h"
#include "RegisterColliderEvent.h"
#include "Game.h"

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

	// get transform node
	transform = static_cast<TransformNode*>(getParent()->getNode(NodeTag::transform_node));
	assert(transform != nullptr);

	circle.setFillColor(sf::Color(255, 255, 255, 80));
	circle.setOutlineColor(sf::Color(0, 128, 0, 124));
	circle.setOutlineThickness(4);
}

void CollisionNode::render()
{
	// draw debug circle
	circle.setPosition(transform->position.x - transform->origin.x, 
		transform->position.y - transform->origin.y);
	getGame()->draw(circle);
}