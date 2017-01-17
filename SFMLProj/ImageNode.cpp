#include "ImageNode.h"
#include "Game.h"

void ImageNode::start()
{
	sf::Texture& txr = getGame()->getTexture(path);
	txr.setSmooth(true);

	sprite.setTexture(txr);
	sprite.setPosition(x, y);
}

void ImageNode::render()
{
	getGame()->draw(sprite);
}

void ImageNode::setScale(float x, float y)
{
	sprite.setScale(x, y);
}