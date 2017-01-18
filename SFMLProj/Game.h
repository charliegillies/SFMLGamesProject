#pragma once

#include <SFML/Graphics.hpp>
#include "TextureLoader.h"
#include "ControlScheme.h"
#include "Camera.h"
#include "EventSystem.h"
#include "Input.h"
#include "FontLoader.h"

class SceneNode;
class Scene;

/*
	Holds the scenes that are running in the game,
	helps handle the transitions, co-ordinates with the
	game loop that is running in the back end.
*/
class Game
{
public:
	Game(Scene* scene, sf::RenderWindow& window);
	~Game();

	// called at the start of the game
	void onStart();

	// called every frame of the game
	void onUpdate();

	// called when the game has complete
	void onExit();

	// called when the game needs to render
	void onRender();

	// changes the current scene to the provided scene
	void changeScene(Scene* scene);

	// draws a sprite
	void draw(sf::Drawable& sprite);

	// loads a texture with a given filepath with the prefix 'Content/'
	sf::Texture& getTexture(const std::string fp);

	// loads a font with a given filepath with the prefix 'Content/'
	sf::Font& getFont(const std::string fp);

	// adds a scene node to the current scene
	void addSceneNode(SceneNode* node);

	// removes a scene node from the current scene
	void removeSceneNode(SceneNode* node);

	// gets the control scheme
	ControlScheme* getControlScheme();

	// gets the camera
	Camera* getCamera();

	// set deltaTime
	void setDt(float dt);

	// get deltaTime
	float deltaTime();

	// gets the global event system that is specific to the scene
	EventSystem* getEventSystem();

	// gets the instance of the input
	Input* getInput();

	// closes the window
	void exitGame();

private:
	float _deltaTime;
	Scene* _currentScene;
	sf::RenderWindow& _window;
	ControlScheme* _controlScheme;
	Camera* _camera;
	Input* _input;

	FontLoader* _fontLoader;
	TextureLoader* _textureLoader;
};