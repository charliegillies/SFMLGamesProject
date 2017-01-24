#include "CollisionNode.h"
#include "EventTags.h"
#include "RegisterColliderEvent.h"
#include "Game.h"
#include "Utils.h"
#include <iostream>

string CollisionNode::getNodeTag()
{
	return NodeTag::collision_node;
}

bool CollisionNode::collides(CollisionNode* testNode)
{
	// test the flag values, if both colliders have flags on
	if (test_flag && testNode->test_flag)
	{
		auto a = maskBits & testNode->categoryBits;
		auto b = testNode->maskBits & categoryBits;

		bool flagsCorrect = a != 0 && b != 0;
		if (!flagsCorrect)
			return false;
	}

	// temporary: if we choose to move away from just circle colliders
	// then this will need to be virtual and overriden.
	// for now, we will just do the circle collision check here.
	int dx = testNode->getX() - getX();
	int dy = testNode->getY() - getY();
	int comb_radius = testNode->radius + radius;
	return (dx*dx) + (dy*dy) < (comb_radius*comb_radius);
}

Raycast CollisionNode::testRaycast(Raycast ray)
{
	// a, b is the start/end points of the line
	auto a = ray.start;
	auto b = ray.end;
	// c is the (x,y) position of the circle
	auto c = sf::Vector2f(getX(), getY());
	// euclidean distance of the start and end point 
	auto lab = Utils::distance(a, b);
	// compute directional vector
	auto d = (b - a) / lab;
	// t is the closest point to the circle center
	auto t = d.x*(c.x - a.x) + d.y*(c.y - a.y);
	// compute the coordinates of the point E on line and closest to c
	auto e = sf::Vector2f(t*d.x + a.x, t*d.y + a.y);
	// now get the distance from the closest point and the circle
	auto lec = Utils::distance(e, c);

	// if we're within radius, the line is touching
	if (lec < radius)
	{
		auto dt = sqrt(pow(radius, 2) - pow(lec, 2));

		// this ensures that the ray is inside of the circle
		// as apposed to the vectors line
		if ((t - dt) < 0 || (t + dt) < 0)
			return ray;

		ray.collider = this;
		ray.hit = true;

		ray.intersect_1.x = (t - dt)*d.x + a.x;
		ray.intersect_1.y = (t - dt)*d.y + a.y;

		ray.intersect_2.x = (t + dt)*d.x + a.x;
		ray.intersect_2.y = (t + dt)*d.y + a.y;
	}

	return ray;
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

void CollisionNode::setFlags(flag category, flag mask)
{
	this->categoryBits = category;
	this->maskBits = mask;
	this->test_flag = true;
}

Raycast CollisionNode::raycast(sf::Vector2f start, sf::Vector2f dir, float range, flag searchCategory)
{


	return _rayUtility->cast(start, dir, range, searchCategory);
}

void CollisionNode::drawCast(Raycast cast)
{
	_rayUtility->drawCast(cast);
}

void CollisionNode::start()
{
	//todo cleanup required
	RegisterColliderEvent register_collider(this);
	invokeGlobalEvent(EventTags::registerCollider, &register_collider);
	_rayUtility = register_collider.rayUtility;

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
	collisionEvent->collider_b = b;
	collisionEvent->collider_a = this;

	// lets all collision event subscribers know that
	// we've just collided with CollisionNode b
	invokeLocalEvent(EventTags::collided, collisionEvent);
}