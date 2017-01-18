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
	// test the flag values, if both colliders have flags on
	if (test_flag && testNode->test_flag)
		if ((collision_flag & testNode->node_flag) == 0) 
			return false;

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

void CollisionNode::setFlags(byte owner_flag, byte collision_flag)
{
	this->node_flag = owner_flag;
	this->collision_flag = collision_flag;
	this->test_flag = true;
}

void CollisionNode::start()
{
	//todo cleanup required
	RegisterColliderEvent register_collider(this);
	invokeGlobalEvent(EventTags::registerCollider, &register_collider);

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

void CollisionNode::onRemoved()
{
	// send global event notifying collision system that we've been removed
	RegisterColliderEvent unregister_collider(this);
	invokeGlobalEvent(EventTags::unregisterCollider, &unregister_collider);
}

void CollisionNode::onCollide(CollisionNode* b)
{
	// if collider node 'b' has a parent, use that, else use b
	SceneNode* collider = (b->getParent() != nullptr) ? b->getParent() : b;
	collisionEvent->collider = collider;

	// lets all collision event subscribers know that
	// we've just collided with CollisionNode b
	invokeLocalEvent(EventTags::collided, collisionEvent);
}