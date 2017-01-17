#pragma once
#include "Scene.h"
#include "Button.h"

/*
	This is the starting scene for the game.
*/
class MenuScene : public Scene
{
public:
	MenuScene();
	~MenuScene();

	void onStart() override;
	void onUpdate() override;

private:
	Button* _gameStartBtn;
	Button* _exitBtn;
};

