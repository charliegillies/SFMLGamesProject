#pragma once
#include "SceneNode.h"
#include "Rectangle.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

/*
	Basic button graphic
*/
class Button : public SceneNode
{
public:
	Button(int x, int y, string txt, string img, int textSize) 
		: rect(x, y, 0, 0), text(txt), img(img), textSize(textSize) {}
	~Button();

	bool hovered();
	bool pressed();

	void render() override;
	void start() override;
	void update() override;

	Button* setTextColor(sf::Color color);

private:
	Rectangle rect;
	string text;
	string img;

	int textSize;

	sf::Text textGraphic;
	sf::Sprite spriteGraphic;
};