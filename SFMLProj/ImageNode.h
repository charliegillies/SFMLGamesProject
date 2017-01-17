#pragma once
#include "SceneNode.h"
#include <SFML/Graphics/Sprite.hpp>

class ImageNode : public SceneNode
{
public:
	ImageNode(int x, int y, string path) : x(x), y(y), path(path), sprite() {};
	~ImageNode() {}

	void start() override;
	void render() override;

	void setScale(float x, float y);

private:
	int x;
	int y;
	string path;
	sf::Sprite sprite;
};

