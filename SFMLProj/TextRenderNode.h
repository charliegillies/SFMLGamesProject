#pragma once
#include "SceneNode.h"
#include <SFML/Graphics/Text.hpp>

class TextRenderNode : public SceneNode
{
public:
	TextRenderNode(string fontPath, string text) : _fontPath(fontPath), _text(text) {}
	~TextRenderNode();

	void start() override;
	void render() override;

private:
	sf::Text _textRenderer;
	string _fontPath;
	string _text;
};