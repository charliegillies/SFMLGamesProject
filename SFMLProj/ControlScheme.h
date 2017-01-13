#pragma once

/*
	Provides a basic interface for rekeybindable actions.
*/
class ControlScheme
{
public:
	// if the player has fired
	bool fired();

	// if the player has moved forwards
	bool forwards();
	
	// if the player has moved backwards
	bool backwards();
};
