#pragma once
#include "TextNode.h"

class AnimatedTextNode : public TextNode
{
public:
	AnimatedTextNode(float animateTime, int x, int y, string font, string msg, sf::Color color, int size)
		: TextNode(x, y, font, msg, color, size), _animateTime(animateTime) { }

	~AnimatedTextNode() { }

	void start() override;
	void update() override;

private:
	string _displayText;
	float _animateTime;
	float _countedTime;

	int index;
	int end;
};
