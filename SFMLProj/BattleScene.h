#pragma once
#include "Scene.h"

/*
	Battle scene where the player engages in combat
	against the enemies that are set.
*/
class BattleScene : public Scene
{
public:
	BattleScene();
	~BattleScene();

	void onStart() override;
};