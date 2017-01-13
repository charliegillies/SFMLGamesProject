#include "ControlScheme.h"
#include <SFML/Window/Keyboard.hpp>

bool ControlScheme::fired()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}