#include "Button.h"
#include "Game.h"

Button::~Button() {}

bool Button::hovered()
{
	sf::Vector2f m = getGame()->getCamera()->getWorldMouse();
	return rect.containsPoint(static_cast<int>(m.x), static_cast<int>(m.y));
}

bool Button::pressed()
{
	return getGame()->getInput()->leftClicked() && hovered();
}

void Button::render()
{
	getGame()->draw(spriteGraphic);

	SceneNode::render();
}

void Button::start()
{
	sf::Texture& tex = getGame()->getTexture(img);
	spriteGraphic.setTexture(tex);
	spriteGraphic.setPosition(rect.x, rect.y);
	rect.width = tex.getSize().x;
	rect.height = tex.getSize().y;
	
	if (childTextNode != nullptr)
	{
		addChild(childTextNode);
		childTextNode->start();
		childTextNode->positionToBounds(rect.x, rect.y, rect.width, rect.height);
	}
}

void Button::update()
{

}

TextNode* Button::getTextNode()
{
	return childTextNode;
}