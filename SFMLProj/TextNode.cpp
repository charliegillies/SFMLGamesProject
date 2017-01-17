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