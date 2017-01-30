#include "TextNode.h"
#include "Game.h"

TextNode::~TextNode() {}

void TextNode::start()
{
	text.setFont(getGame()->getFont(font));
	text.setPosition(x, y);
	text.setString(msg);
	text.setFillColor(color);
	text.setCharacterSize(size);
}

void TextNode::render()
{
	getGame()->draw(text);
}

void TextNode::positionToBounds(int ix, int iy, int width, int height)
{
	auto bounds = text.getGlobalBounds();

	text.setOrigin(0, bounds.height / 2);
	x = ix + ((width / 2) - (bounds.width / 2));
	y = iy + ((height / 2) - (bounds.height / 2));
	text.setPosition(x, y);
}

void TextNode::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

void TextNode::setText(string txt)
{
	msg = txt;
	text.setString(txt);
}
