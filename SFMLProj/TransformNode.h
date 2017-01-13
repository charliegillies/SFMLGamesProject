#pragma once
#include "SceneNode.h"
#include <SFML/System/Vector2.hpp>

class TransformNode : public SceneNode
{
public:
	TransformNode() : SceneNode(), position(0, 0), scale(1,1), rotation(0), origin(0, 0) {}
	~TransformNode() {}

	// (x, y) position of the node
	sf::Vector2<float> position;
	// (x, y) scale of the node
	sf::Vector2<float> scale;
	// rotation of the node
	float rotation;
	// origin position for rotation
	sf::Vector2<float> origin;

	virtual string getNodeTag() override
	{
		return NodeTag::transform_node;
	};
};