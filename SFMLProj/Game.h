#pragma once

class Game
{
public:
	Game();
	~Game();

	// Called at the start of the game
	void OnStart();

	// Called every frame of the game
	void OnUpdate();

	// Called when the game has complete
	void OnExit();
};