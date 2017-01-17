#include "Input.h"

void Input::setKeyboardState(KeyboardState state)
{
	_lastFrameState = _frameState;
	_frameState = state;
}

bool Input::isKeyDown(sf::Keyboard::Key key)
{
	return !_lastFrameState.keys[key] && _frameState.keys[key];
}

bool Input::keyPressed(sf::Keyboard::Key key)
{
	return _frameState.keys[key];
}