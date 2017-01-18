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

	_debugText.setPosition(0, 60);
	_debugText.setFillColor(sf::Color::White);
	_debugText.setFont(getFont("Fonts//kenvector_future.ttf"));
	_debugText.setCharacterSize(12);
}

Game::~Game() {}

void Game::onStart()
{
	if (_currentScene != nullptr)
		_currentScene->onStart();
}

void Game::onUpdate()
{
	// reset debug
	_debugStr = "DEBUG STATS\n";

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

	// render debug
	_camera->switchToUIView();
	_debugText.setString(_debugStr);
	draw(_debugText);
	_camera->switchToGameView();
}

void Game::changeScene(Scene* scene)
{
	// give scene a reference to game
	scene->setGame(this);

	// exit the current scene 
	if (_currentScene != nullptr)
	{
		_currentScene->onExit();
		_currentScene = scene;
		scene->onStart();
	}
	else
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

void Game::removeSceneNode(SceneNode* node)
{
	assert(_currentScene != nullptr);
	_currentScene->removeSceneNode(node);
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

void Game::setDebugValue(std::string key, std::string value)
{
	string line = key + ": " + value + "\n";
	_debugStr += line;
}

void Game::exitGame()
{
	if (_currentScene != nullptr)
		_currentScene->onExit();

	_window.close();
}

void Game::draw(sf::Drawable& sprite)
{
	_window.draw(sprite);
}