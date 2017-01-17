#pragma once
#include <SFML/Window/Keyboard.hpp>

/*
	Simple struct that holds a 256 element bool array 
	representing each pressable key.
*/
struct KeyboardState
{
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

	// set the current keyboard state, this should happen
	// only as much as once a frame - at most.
	void setKeyboardState(KeyboardState state);

	// checks if the key has been pressed and is still held down
	bool isKeyDown(sf::Keyboard::Key key);

	// checks if the key has been pressed at all
	bool keyPressed(sf::Keyboard::Key key);

private:
	// this frame & last frames keyboard state
	KeyboardState _frameState;
	KeyboardState _lastFrameState;
};