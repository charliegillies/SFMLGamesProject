#include "TextRenderNode.h"
#include "Game.h"

TextRenderNode::~TextRenderNode()
{
}

void TextRenderNode::start()
{
	_textRenderer.setFont(getGame()->getFont(_fontPath));
	_textRenderer.setPosition(0, 0);
	_textRenderer.setCharacterSize(12);
	_textRenderer.setString(_text);
}

void TextRenderNode::render()
{
	getGame()->getCamera()->switchToUIView();
	getGame()->draw(_textRenderer);
	getGame()->getCamera()->switchToGameView();
}