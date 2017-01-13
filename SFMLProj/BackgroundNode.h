#pragma once
#include "SceneNode.h"
#include <SFML/Graphics/Sprite.hpp>
#include "TransformNode.h"

class BackgroundNode : public SceneNode
{
public:
	BackgroundNode();
	~BackgroundNode();

	void start() override;

	void render() override;

	void update() override;

private:
	TransformNode* _transform;
	sf::Sprite _sprite;
};