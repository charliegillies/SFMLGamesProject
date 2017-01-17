#pragma once
#include "SceneNode.h"
#include <SFML/Graphics/CircleShape.hpp>
#include "TransformNode.h"

/*
	Basic scene node that contains data about collision.
*/
class CollisionNode : public SceneNode
{
public:
	explicit CollisionNode(bool isStatic, float radius) 
		: isStatic(isStatic), radius(radius), circle(radius) {}
	
	~CollisionNode() {}

	void start() override;
	void render() override;

	virtual string getNodeTag() override;
	// tests if the two circles collide or not
	bool collides(CollisionNode* test_node);

	// defines if this object will or will not move (not including rotation!)
	// this makes it easier to perform basic collision tests.
	const bool isStatic;

private:
	TransformNode* transform;
	float radius;
	sf::CircleShape circle;
};
