#pragma once
#include "SceneNode.h"
#include "TransformNode.h"

class RotationNode : public SceneNode
{
public:
	RotationNode(float rotPerSecond);
	~RotationNode();

	void update() override;

	void start() override;

private:
	TransformNode* _transform;
	float _rotPerSecond;
};
