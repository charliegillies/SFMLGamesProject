#pragma once
#include "SceneNode.h"
#include <SFML/Graphics/Sprite.hpp>

/*
	A status bar is a moving bar like the health bar or energy bar.
*/
class StatusBar : public SceneNode
{
public:
	StatusBar(string l_fp, string m_fp, string r_fp, int x, int y, int width)
		: l_fp(l_fp), m_fp(m_fp), r_fp(r_fp), l_sprite(), m_sprite(), r_sprite(), x(x),
			y(y), width(width) { }

	~StatusBar() { }

	// Sets the bars width depending on the percentage value.
	// value should never be lower than 0 or higher than 100.
	void setBarPerc(float perc);

	void render() override;
	void start() override;

private:
	string l_fp;
	string m_fp;
	string r_fp;

	sf::Sprite l_sprite;
	sf::Sprite m_sprite;
	sf::Sprite r_sprite;
	
	int x;
	int y;
	int width;
	int height;
	int max_bar_size;
};

