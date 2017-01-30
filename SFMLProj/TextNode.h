#pragma once
#include "SceneNode.h"
#include <SFML/Graphics/Text.hpp>

class TextNode : public SceneNode
{
public:
	TextNode(int x, int y, string font, string msg, sf::Color color, int size)
		: size(size), x(x), y(y), font(font), msg(msg), color(color) {}
	
	~TextNode();

	void start() override;
	void render() override;

	void positionToBounds(int x, int y, int width, int height);

	void setPosition(int x, int y);

	void setText(string txt);

protected:
	int size;
	int x;
	int y;
	string font;
	string msg;
	sf::Text text;
	sf::Color color;
};

