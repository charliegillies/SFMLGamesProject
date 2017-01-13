#pragma once
#include "SceneNode.h"

class CircleColliderNode : public SceneNode
{
public:
	CircleColliderNode();
	~CircleColliderNode();

	virtual string getNodeTag() override;

	// tests if the two circles collide or not
	bool collides(CircleColliderNode* test_node);
};
