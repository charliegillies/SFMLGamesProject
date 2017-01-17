#include "ControlScheme.h"
#include <SFML/Window/Keyboard.hpp>

bool ControlScheme::fired()
{
	return _input->isKeyDown(sf::Keyboard::Space);
}

bool ControlScheme::forwards()
{
	return _input->keyPressed(sf::Keyboard::W);
}

bool ControlScheme::backwards()
{
	return _input->keyPressed(sf::Keyboard::S);
}