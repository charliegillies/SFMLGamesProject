#pragma once
#include "SceneNode.h"

class CollisionNode : public SceneNode
{
public:
	explicit CollisionNode(bool isStatic) : isStatic(isStatic) {}
	~CollisionNode() {}

	virtual string getNodeTag() override;

	// tests if the two circles collide or not
	bool collides(CollisionNode* test_node);

	void start() override;

	// defines if this object will or will not move (not including rotation!)
	// this makes it easier to perform basic collision tests.
	const bool isStatic;
};
