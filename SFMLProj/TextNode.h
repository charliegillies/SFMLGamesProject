#pragma once
#include "SceneNode.h"
#include <SFML/Graphics/Text.hpp>

class TextNode : public SceneNode
{
public:
	TextNode(int x, int y, string font, string msg, sf::Color color, int size)
		: x(x), y(y), font(font), msg(msg), color(color), size(size) {}
	~TextNode();

	void start() override;
	void render() override;

private:
	int size;
	int x;
	int y;
	string font;
	string msg;
	sf::Text text;
	sf::Color color;
};

