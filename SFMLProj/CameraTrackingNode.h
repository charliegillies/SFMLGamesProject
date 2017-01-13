#pragma once
#include "SceneNode.h"
#include "Camera.h"
#include "TransformNode.h"


class CameraTrackingNode : public SceneNode
{
public:
	CameraTrackingNode(int xOffset, int yOffset) : _xOffset(xOffset), _yOffset(yOffset) {}
	~CameraTrackingNode() {}

	void start() override;
	void update() override;

private:
	Camera* _camera;
	TransformNode* _transform;
	int _xOffset;
	int _yOffset;
};

