#include "BackgroundNode.h"
#include "Game.h"

void BackgroundNode::start()
{
	sf::Texture& txr = getGame()->getTexture(filepath);
	_sprite.setTexture(txr);
	txr.setSmooth(true);
	txr.setRepeated(true);
	_sprite.setTextureRect({ 0, 0, 1280, 720 });
	_sprite.setPosition(0, 0);
}

void BackgroundNode::render()
{
	getGame()->getCamera()->switchToUIView();
	getGame()->draw(_sprite);
	getGame()->getCamera()->switchToGameView();
}