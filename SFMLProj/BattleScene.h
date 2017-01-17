#pragma once
#include "Scene.h"

/*
	Scene for testing mechanics.
*/
class BattleScene : public Scene
{
public:
	BattleScene();
	~BattleScene();

	void onStart() override;
};