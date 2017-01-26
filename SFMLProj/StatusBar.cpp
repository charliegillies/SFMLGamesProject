#include "StatusBar.h"
#include "Game.h"

void StatusBar::setBarPerc(float perc)
{
	// calculate bar size
	float bar_size = (max_bar_size / 100.0f) * perc;
	// set bar width using texture rect
	m_sprite.setTextureRect({ 0, 0, static_cast<int>(bar_size), height });
	// now position the right one to be in the correct place
	r_sprite.setPosition(m_sprite.getPosition() + sf::Vector2f(bar_size, 0));
}

void StatusBar::render()
{
	getGame()->draw(l_sprite);
	getGame()->draw(m_sprite);
	getGame()->draw(r_sprite);
}

void StatusBar::start()
{
	auto& l_txr = getGame()->getTexture(l_fp);
	auto& m_txr = getGame()->getTexture(m_fp);
	auto& r_txr = getGame()->getTexture(r_fp);

	// configure l and r
	l_sprite.setTexture(l_txr);
	r_sprite.setTexture(r_txr);

	// configure m
	m_txr.setRepeated(true);
	m_sprite.setTexture(m_txr);

	max_bar_size = width - (l_txr.getSize().x + r_txr.getSize().x);

	// this should only need to be set once
	l_sprite.setPosition(x, y);
	m_sprite.setPosition(x + l_txr.getSize().x, y);

	height = l_txr.getSize().y;

	// calculates the rest of it
	setBarPerc(100);
}