#include "SpriteNode.h"
#include "Game.h"

SpriteNode::~SpriteNode()
{
	_transform = nullptr;
}

void SpriteNode::start()
{
	sf::Texture& txr = getGame()->getTexture(_path);
	_sprite.setTexture(txr);
	txr.setSmooth(true);

	_transform = static_cast<TransformNode*>(getParent()->getNode(NodeTag::transform_node));
	// ensure that _transform is not null
	assert(_transform != nullptr);

}

void SpriteNode::render()
{
	getGame()->draw(_sprite);
}

void SpriteNode::update()
{
	// use the transform data to set the sprite information
	_sprite.setPosition(_transform->position);
	_sprite.setScale(_transform->scale);
	_sprite.setRotation(_transform->rotation);
	_sprite.setOrigin(_transform->origin);
}

string SpriteNode::getNodeTag()
{
	return NodeTag::sprite_node;
}