#pragma once
#include "SceneNode.h"
#include <SFML/Graphics/CircleShape.hpp>
#include "TransformNode.h"
#include "CollisionEvent.h"
#include "stdint.h"

typedef uint8_t byte;

/*
	Basic scene node that contains data about collision.
*/
class CollisionNode : public SceneNode
{
public:
	static const byte NO_MASK = 0;
	static const byte PLAYER_MASK = 1;
	static const byte OBSTACLE_MASK = 2;
	static const byte ENEMY_MASK = 4;
	static const byte ALL_MASKS = PLAYER_MASK | OBSTACLE_MASK | ENEMY_MASK;

	explicit CollisionNode(float radius, sf::Vector2f offset = sf::Vector2f(0,0)) 
		: radius(radius), test_flag(false), node_flag(NO_MASK), 
		collision_flag(NO_MASK), offset(offset), circle(radius)
	{
		// ensures generation of unique num for every collider
		static int gId = 0;
		_id = ++gId;

		collisionEvent = new CollisionEvent();
	}
	
	~CollisionNode() {}

	void start() override;
	void render() override;

	// this is called when this collision node collides 
	// with another known collision node. 
	void onCollide(CollisionNode* b);

	virtual string getNodeTag() override;

	// tests if the two circles collide or not
	bool collides(CollisionNode* test_node);

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

	// automatically turns test_flag on, meaning that flags will
	// be compared during the collides test method.
	// this allows us to filter out unwanted collision responses with ease.
	void setFlags(byte ownerFlag, byte collision_flag);

private:
	int _id;
	float radius;

	// if the flag should be tested or not during collision
	bool test_flag;
	// the bits representing who owns this collision node
	byte node_flag;
	// the bits representing who this node can collide with
	byte collision_flag;
	
	// a local copy of the collision event that will be
	// reused as it is broadcasted to our parent when we collide.
	CollisionEvent* collisionEvent;
	
	// offset position of the collider, if any
	sf::Vector2f offset;

	TransformNode* transform;
	sf::CircleShape circle;
};
