#pragma once
#include "SceneNode.h"
#include <SFML/System/Vector2.hpp>
#include "TransformNode.h"

/*
	Moves a node along a specific given velocity.
*/
class VelocityNode : public SceneNode
{
public:
	VelocityNode(float speed, sf::Vector2f direction) : _speed(speed), _direction(direction) {}
	~VelocityNode() {}

	void start() override;
	void update() override;

private:
	float _speed;
	sf::Vector2f _direction;
	TransformNode* _transform;
};