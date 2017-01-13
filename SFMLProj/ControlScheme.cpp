#include "ControlScheme.h"
#include <SFML/Window/Keyboard.hpp>

bool ControlScheme::fired()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

bool ControlScheme::forwards()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::W);
}

bool ControlScheme::backwards()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::S);
}