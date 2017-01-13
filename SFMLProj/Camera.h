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
	Camera(sf::RenderWindow* window);

	// set the center position of the cameera
	void setCenter(float x, float y);

	// get the size of the camera's viewport
	sf::Vector2<float> getSize();

	// get the world mouse position, converted co-ordinates
	sf::Vector2<float> getWorldMouse();

private:
	sf::RenderWindow* _window;
	sf::View view;
};
