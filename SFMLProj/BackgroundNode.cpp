#include "BackgroundNode.h"
#include "Game.h"

BackgroundNode::BackgroundNode() {}
BackgroundNode::~BackgroundNode() {}

void BackgroundNode::start()
{
	sf::Texture& txr = getGame()->getTexture("purple.png");
	_sprite.setTexture(txr);
	txr.setSmooth(true);
	txr.setRepeated(true);
	_sprite.setTextureRect({ 0, 0, 1280, 720 });
	
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

void BackgroundNode::render()
{
	getGame()->drawSprite(_sprite);
}

void BackgroundNode::update()
{
	// reposition
	auto camera = getGame()->getCamera();
	auto cam_size = camera->getSize();
	cam_size.x = cam_size.x / 2;
	cam_size.y = cam_size.y / 2;
	_transform->position = camera->getCameraPos() - cam_size;

	// use the transform data to set the sprite information
	_sprite.setPosition(_transform->position);
	_sprite.setScale(_transform->scale);
	_sprite.setRotation(_transform->rotation);
	_sprite.setOrigin(_transform->origin);
}