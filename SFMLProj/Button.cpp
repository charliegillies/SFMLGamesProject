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

	textGraphic.setFont(getGame()->getFont("Fonts//kenvector_future_thin.ttf"));
	textGraphic.setString(text);
	textGraphic.setCharacterSize(textSize);
	textGraphic.setPosition(rect.x, rect.y);

	sf::Rect<float> bounds = textGraphic.getGlobalBounds();
	textGraphic.setOrigin(0, bounds.height / 2);
	auto x = rect.x + ((rect.width/2) - (bounds.width/2));
	auto y = rect.y + ((rect.height/2) - (bounds.height/2));
	textGraphic.setPosition(x, y);
}

void Button::update()
{

}

Button* Button::setTextColor(sf::Color color)
{
	textGraphic.setFillColor(color);
	return this;
}