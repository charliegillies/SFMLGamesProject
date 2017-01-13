#include "SpriteNode.h"
#include "Game.h"

SpriteNode::~SpriteNode() {}

void SpriteNode::start()
{
	_sprite.setTexture(getGame()->getTexture(_path));
}

void SpriteNode::render()
{
	getGame()->drawSprite(_sprite);
}