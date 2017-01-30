#include "AnimatedTextNode.h"
#include "Game.h"

void AnimatedTextNode::start()
{
	TextNode::start();

	_displayText = "";
	text.setString(_displayText);

	index = 0;
	end = msg.size();
}

void AnimatedTextNode::update()
{
	// ensure it does not go out of bounds
	if (index == end) return;

	_countedTime += getGame()->deltaTime();

	if (_countedTime >= _animateTime)
	{
		_countedTime = _countedTime - _animateTime;

		// move text along..
		_displayText += msg[index];
		index++;

		text.setString(_displayText);
	}
}
