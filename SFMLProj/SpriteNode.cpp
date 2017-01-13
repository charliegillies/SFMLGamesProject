#include "SpriteNode.h"
#include "Game.h"

SpriteNode::~SpriteNode()
{
	_transform = nullptr;
}

void SpriteNode::start()
{
	_sprite.setTexture(getGame()->getTexture(_path));

	// try and get a transform node
	SceneNode* node;
	if (getParent() != nullptr)
	{
		node = getParent()->getNode(NodeTag::transform_node);
		
		// attempt cast
		if (node != nullptr)
			_transform = static_cast<TransformNode*>(node);
	}

	// ensure that _transform is not null
	assert(_transform != nullptr);
}

void SpriteNode::render()
{
	getGame()->drawSprite(_sprite);
}

void SpriteNode::update()
{
	_sprite.setPosition(_transform->position);
}

string SpriteNode::getNodeTag()
{
	return NodeTag::sprite_node;
}