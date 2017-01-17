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
	Simple struct that holds data about the mouse state
	during a single frame in the game.
*/
struct MouseState
{
	bool leftClicked;
	bool rightClicked;
	int screenX;
	int screenY;
};

/*
	Input management utility.
*/
class Input
{
public:
	Input() {}
	~Input() {}

	// set the current keyboard state, this should happen
	// only as much as once a frame - at most.
	void setKeyboardState(KeyboardState state);

	// set the current mouse state, this should happen
	// only as much as once a frame - at most.
	void setMouseState(MouseState state);

	// checks if the key has been pressed and is still held down
	bool isKeyDown(sf::Keyboard::Key key);

	// checks if the key has been pressed at all
	bool keyPressed(sf::Keyboard::Key key);

	// checks if the left click has been pressed and is still held down
	bool leftClickDown();

	// checks if there has been a left click
	bool leftClicked();

	// checks if the left click has been pressed and is still down
	bool rightClickDown();

	// checks if there has been a right click
	bool rightClick();

	// get the screen X value
	int getX();

	// get the screen Y value
	int getY();

private:
	// this frame & last frames keyboard state
	KeyboardState _kbFrameState;
	KeyboardState _kbLastFrameState;

	// this frame & last frames mouse state
	MouseState _mFrameState;
	MouseState _mLastFrameState;
};