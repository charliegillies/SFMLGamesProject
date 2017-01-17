#pragma once
#include <SFML/Window/Keyboard.hpp>

struct KeyboardState
{
	// bool array representing all 256 pressable keys
	bool keys[256];
};

/*
	Input management class.
*/
class Input
{
public:
	Input() {}
	~Input() {}

	void setKeyboardState(KeyboardState state);

	bool isKeyDown(sf::Keyboard::Key key);

	bool keyPressed(sf::Keyboard::Key key);

private:
	// this frame & last frames keyboard state
	KeyboardState _frameState;
	KeyboardState _lastFrameState;
};