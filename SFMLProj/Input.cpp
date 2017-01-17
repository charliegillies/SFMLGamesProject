#include "Input.h"

void Input::setKeyboardState(KeyboardState state)
{
	_kbLastFrameState = _kbFrameState;
	_kbFrameState = state;
}

void Input::setMouseState(MouseState state)
{
	_mLastFrameState = _mFrameState;
	_mFrameState = state;
}

bool Input::isKeyDown(sf::Keyboard::Key key)
{
	return !_kbLastFrameState.keys[key] && _kbFrameState.keys[key];
}

bool Input::keyPressed(sf::Keyboard::Key key)
{
	return _kbFrameState.keys[key];
}