#pragma once
#include "Scene.h"

class LevelOneScene : public Scene
{
public:
	LevelOneScene();
	~LevelOneScene();

	void onStart() override;
};