#pragma once
#include "SceneNode.h"
#include <SFML/Graphics/Sprite.hpp>
#include "TransformNode.h"

class BackgroundNode : public SceneNode
{
public:
	BackgroundNode(std::string filepath) : filepath(filepath) {};
	~BackgroundNode() {}

	void start() override;

	void render() override;

private:
	sf::Sprite _sprite;
	std::string filepath;
};