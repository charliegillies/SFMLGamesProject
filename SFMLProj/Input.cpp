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

bool Input::leftClickDown()
{
	return _mLastFrameState.leftClicked && _mFrameState.leftClicked;
}

bool Input::leftClicked()
{
	return !_mLastFrameState.leftClicked && _mFrameState.leftClicked;
}

bool Input::rightClickDown()
{
	return _mLastFrameState.rightClicked && _mFrameState.rightClicked;
}

bool Input::rightClicked()
{
	return !_mLastFrameState.rightClicked && _mFrameState.rightClicked;
}

int Input::getX()
{
	return _mFrameState.screenX;
}

int Input::getY()
{
	return _mFrameState.screenY;
}