#include "ControlScheme.h"
#include <SFML/Window/Keyboard.hpp>

bool ControlScheme::shieldUp()
{
	return _input->keyPressed(sf::Keyboard::Space);
}

bool ControlScheme::primaryFired()
{
	return _input->leftClicked();
}

bool ControlScheme::secondaryFired()
{
	return _input->rightClicked();
}

bool ControlScheme::forwards()
{
	return _input->keyPressed(sf::Keyboard::W);
}

bool ControlScheme::backwards()
{
	return _input->keyPressed(sf::Keyboard::S);
}