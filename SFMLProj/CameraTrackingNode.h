#pragma once
#include "SceneNode.h"
#include "Camera.h"
#include "TransformNode.h"

/*
	Makes the camera focus on the position of the scene node.
*/
class CameraTrackingNode : public SceneNode
{
public:
	CameraTrackingNode() {}
	~CameraTrackingNode() {}

	void start() override;
	void update() override;

private:
	sf::Vector2f top_left;
	sf::Vector2f bot_right;

	Camera* _camera;
	TransformNode* _transform;
};