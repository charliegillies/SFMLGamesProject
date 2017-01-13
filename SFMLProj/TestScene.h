#pragma once
#include "Scene.h"

/*
	Scene for testing mechanics.
*/
class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	void onStart() override;
};