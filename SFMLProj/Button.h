#pragma once
#include "SceneNode.h"
#include "Rectangle.h"
#include <SFML/Graphics/Sprite.hpp>
#include "TextNode.h"

/*
	Basic button graphic
*/
class Button : public SceneNode
{
public:
	Button(int x, int y, string img, TextNode* potentialChild) 
		: rect(x, y, 0, 0), img(img)
	{
		childTextNode = potentialChild;
	}

	~Button();

	bool hovered();
	bool pressed();

	void render() override;
	void start() override;
	void update() override;

	TextNode* getTextNode();

private:
	TextNode* childTextNode;
	Rectangle rect;
	string img;
	sf::Sprite spriteGraphic;
};