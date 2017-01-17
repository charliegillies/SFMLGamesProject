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
	getGame()->draw(textGraphic);
}

void Button::start()
{
	sf::Texture& tex = getGame()->getTexture(img);
	spriteGraphic.setTexture(tex);
	spriteGraphic.setPosition(rect.x, rect.y);
	rect.width = tex.getSize().x;
	rect.height = tex.getSize().y;

	textGraphic.setFont(getGame()->getFont("Fonts//kenvector_future.ttf"));
	textGraphic.setString(text);
	textGraphic.setCharacterSize(textSize);
	textGraphic.setPosition(rect.x, rect.y);
}

void Button::update()
{

}

Button* Button::setTextColor(sf::Color color)
{
	textGraphic.setFillColor(color);
	return this;
}