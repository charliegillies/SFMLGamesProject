#pragma once

/*
	Holds the scenes that are running in the game,
	helps handle the transitions, co-ordinates with the
	game loop that is running in the back end.
*/
class Game
{
public:
	Game();
	~Game();

	// Called at the start of the game
	void onStart();

	// Called every frame of the game
	void onUpdate();

	// Called when the game has complete
	void onExit();
};