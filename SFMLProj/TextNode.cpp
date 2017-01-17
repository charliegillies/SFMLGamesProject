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
	auto x = ix + ((width / 2) - (bounds.width / 2));
	auto y = iy + ((height / 2) - (bounds.height / 2));
	text.setPosition(x, y);
}