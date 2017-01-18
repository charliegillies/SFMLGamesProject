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
	// temporary: if we choose to move away from just circle colliders
	// then this will need to be virtual and overriden.
	// for now, we will just do the circle collision check here.

	int dx = testNode->getX() - getX();
	int dy = testNode->getY() - getY();
	int comb_radius = testNode->radius + radius;
	return (dx*dx) + (dy*dy) < (comb_radius*comb_radius);
}

int CollisionNode::getTopX()
{
	return transform->position.x + offset.x - transform->origin.x;
}

int CollisionNode::getTopY()
{
	return transform->position.y + offset.y - transform->origin.y;
}

int CollisionNode::getX()
{
	return transform->position.x + offset.x;
}

int CollisionNode::getY()
{
	return transform->position.y + offset.y;
}

int CollisionNode::getWidth()
{
	return radius * 2;
}

int CollisionNode::getHeight()
{
	return radius * 2;
}

int CollisionNode::getID() const
{
	return _id;
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
	circle.setOutlineThickness(3);
}

void CollisionNode::render()
{
	// draw debug circle
	circle.setPosition(getX(), getY());
	circle.setOrigin(transform->origin);
	
	getGame()->draw(circle);
}

void CollisionNode::onCollide(CollisionNode* b)
{
	// now.. we need to figure out what sort of design decision
	// we should make here. Two choices being either:
	// a) make an event specific to the entity that owns our node (parent)
	//    that allows all nodes to subscribe to the potential collision
	//	  without ever finding the collision node.
	// b) or.. put a signal/delegate on the collision node and let other nodes
	//    find and subscribe to it. 


}