#pragma once
#include "SceneNode.h"
#include <SFML/Graphics/Sprite.hpp>
#include "TransformNode.h"

/*
	A scene node that renders a specific sprite onto the screen.
*/
class SpriteNode : public SceneNode
{
public:
	SpriteNode(string path) : SceneNode(), _path(path), _sprite() {}
	~SpriteNode();

	void start() override;

	void render() override;

	void update() override;

	virtual string getNodeTag() override;

private:
	TransformNode* _transform;
	string _path;
	sf::Sprite _sprite;
};
