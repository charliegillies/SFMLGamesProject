#include "Camera.h"
#include <SFML/Window/Mouse.hpp>

Camera::Camera(sf::RenderWindow& window) : _window(window)
{
	_view = _window.getDefaultView();
	_uiView = _window.getDefaultView();
	_window.setView(_view);
}

void Camera::setCenter(float x, float y)
{
	_view.setCenter(x, y);
	_window.setView(_view);
}

sf::Vector2<float> Camera::getSize()
{
	auto size = _view.getSize();
	return sf::Vector2<float>(size.x, size.y);
}

sf::Vector2<float> Camera::getWorldMouse()
{
	// get the current mouse position in the window
	sf::Vector2i pixelPos = sf::Mouse::getPosition(_window);

	// convert it to world coordinates
	sf::Vector2f worldPos = _window.mapPixelToCoords(pixelPos);

	return worldPos;
}

sf::Vector2<float> Camera::getCameraPos()
{
	return _view.getCenter();
}

void Camera::switchToUIView()
{
	_window.setView(_uiView);
}

void Camera::switchToGameView()
{
	_window.setView(_view);
}