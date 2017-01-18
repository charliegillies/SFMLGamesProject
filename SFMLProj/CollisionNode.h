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
	explicit CollisionNode(bool isStatic, float radius, sf::Vector2f offset = sf::Vector2f(0,0)) 
		: isStatic(isStatic), radius(radius), circle(radius)
	{
		// ensures generation of unique num for every collider
		static int gId = 0;
		_id = ++gId;
	}
	
	~CollisionNode() {}

	void start() override;
	void render() override;

	virtual string getNodeTag() override;
	// tests if the two circles collide or not
	bool collides(CollisionNode* test_node);

	// defines if this object will or will not move (not including rotation!)
	// this makes it easier to perform basic collision tests.
	const bool isStatic;

	// gets the x co-ordinate of the top left hand side of the collider
	int getTopX();

	// gets the y co-ordinate of the top left hand side of the collider
	int getTopY();

	// gets the x co-ordinate of the collider with the offset (if any) applied
	int getX();

	// gets the y co-ordinate of the collider with the offset (if any) applied
	int getY();

	// gets the width of the collider
	// for a circle this is just radius*2
	int getWidth();

	// gets the height of the collider
	// for a circle, this is just radius*2
	int getHeight();

	// gets the unique id of this collider, which should
	// be used for generating hashes or fast obj comparison
	int getID() const;

private:
	int _id;
	float radius;
	
	// offset position of the collider, if any
	sf::Vector2f offset;

	TransformNode* transform;
	sf::CircleShape circle;
};
