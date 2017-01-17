#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

/*
	The camera is an interface that SceneNodes can use to
	manipulate the view matrix and tools can use for 
	graphics settings (resolution, etc). As well as 
	mouse co-ordinate conversion, etc.
*/
class Camera
{
public:
	explicit Camera(sf::RenderWindow& window);

	// set the center position of the cameera
	void setCenter(float x, float y);

	// get the size of the camera's viewport
	sf::Vector2<float> getSize();

	// get the world mouse position, converted co-ordinates
	sf::Vector2<float> getWorldMouse();

	// gets the position of the camera in the world.
	sf::Vector2<float> getCameraPos();

	// switches to the ui view for UI rendering.
	void switchToUIView();

	// switches back to game view for actor rendering.
	void switchToGameView();

private:
	sf::RenderWindow& _window;
	sf::View _view;
	sf::View _uiView;
};
