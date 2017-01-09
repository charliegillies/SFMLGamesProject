#pragma once
#include "Scene.h"
#include <SFML/Graphics/Sprite.hpp>

/*
	Scene for testing mechanics.
*/
class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	void onStart() override;
	void onExit() override;
	void onUpdate() override;

private:
	sf::Sprite sprite;
};