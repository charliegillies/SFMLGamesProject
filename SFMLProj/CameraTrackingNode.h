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

	sf::Vector2f lerp_position;
	float lerp_time;

	// calculates the target movement position
	// which also keeps the camera inside of the
	// top_left and bot_right specified bounds.
	sf::Vector2f getTargetPosition();

	Camera* _camera;
	TransformNode* _transform;
};