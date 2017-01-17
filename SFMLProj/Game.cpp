#include "Game.h"
#include "Scene.h"

Game::Game(Scene* scene, sf::RenderWindow& window) : _window(window)
{
	changeScene(scene);
	this->_input = new Input();

	// create asset loaders..
	this->_textureLoader = new TextureLoader();
	this->_fontLoader = new FontLoader();
	
	this->_controlScheme = new ControlScheme(_input);
	this->_camera = new Camera(window);
	this->_deltaTime = 0;
}

Game::~Game() {}

void Game::onStart()
{
	if (_currentScene != nullptr)
		_currentScene->onStart();
}

void Game::onUpdate()
{
	if (_currentScene != nullptr)
		_currentScene->onUpdate();
}

void Game::onExit()
{
	if (_currentScene != nullptr)
		_currentScene->onExit();
}

void Game::onRender()
{
	if (_currentScene != nullptr)
		_currentScene->onRender();
}

void Game::changeScene(Scene* scene)
{
	// exit the current scene 
	if (_currentScene != nullptr)
		_currentScene->onExit();

	// give scene a reference to game
	scene->setGame(this);
	// store a local reference to the current scene
	_currentScene = scene;
}

sf::Texture& Game::getTexture(const std::string fp)
{
	return _textureLoader->get(fp);
}

sf::Font& Game::getFont(const std::string fp)
{
	return _fontLoader->get(fp);
}

void Game::addSceneNode(SceneNode* node)
{
	if (_currentScene == nullptr) return;

	node->setGame(this);
	_currentScene->addSceneNode(node);
}

ControlScheme* Game::getControlScheme()
{
	return _controlScheme;
}

Camera* Game::getCamera()
{
	return _camera;
}

void Game::setDt(float dt)
{
	_deltaTime = dt;
}

float Game::deltaTime()
{
	return _deltaTime;
}

EventSystem* Game::getEventSystem()
{
	return _currentScene != nullptr ? _currentScene->getEventSystem() : nullptr;
}

Input* Game::getInput()
{
	return _input;
}

void Game::draw(sf::Drawable& sprite)
{
	_window.draw(sprite);
}