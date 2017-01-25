#pragma once
#include "Input.h"

/*
	Provides a basic interface for rekeybindable actions.
*/
class ControlScheme
{
public:
	explicit ControlScheme(Input* input)
	{
		this->_input = input;
	}

	~ControlScheme() {}

	bool shieldUp();

	// if the player has fired
	bool primaryFired();

	// if the secondary has fired
	bool secondaryFired();

	// if the player has moved forwards
	bool forwards();
	
	// if the player has moved backwards
	bool backwards();

private:
	Input* _input;
};
