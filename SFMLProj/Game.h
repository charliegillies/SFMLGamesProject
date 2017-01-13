#pragma once

#include <SFML/Graphics.hpp>
#include "TextureLoader.h"

class Scene;

/*
	Holds the scenes that are running in the game,
	helps handle the transitions, co-ordinates with the
	game loop that is running in the back end.
*/
class Game
{
public:
	Game(Scene* scene, sf::RenderWindow* window);
	~Game();

	// called at the start of the game
	void onStart();

	// called every frame of the game
	void onUpdate();

	// called when the game has complete
	void onExit();

	// changes the current scene to the provided scene
	void changeScene(Scene* scene);

	// draws a sprite
	void drawSprite(sf::Sprite sprite);

	// loads a texture with a given filepath with the prefix 'Content/'
	sf::Texture& getTexture(const std::string fp);

private:
	Scene* _currentScene;
	sf::RenderWindow* _window;
	
	TextureLoader* textureLoader;
};