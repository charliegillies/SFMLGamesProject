#pragma once
#include "SceneNode.h"
#include <SFML/Graphics/Sprite.hpp>

/*
	A scene node that renders a specific sprite onto the screen.
*/
class SpriteNode : public SceneNode
{
public:
	SpriteNode(std::string path) : SceneNode(), _path(path), _sprite() {}
	~SpriteNode();

	void start() override;

	void render() override;

private:
	std::string _path;
	sf::Sprite _sprite;
};
