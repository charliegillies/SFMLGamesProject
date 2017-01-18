#pragma once
#include <SFML/System/Vector2.hpp>

/*
	Utils class for general useful functions that aren't relevant
	to any one specific object.
*/
class Utils
{
public:
	static float clamp(float value, float min, float max);

	static float easeSmoothStep(float currentTime, float lerpTime);

	static sf::Vector2f normalize(sf::Vector2f source);

	static float lerp(float a, float b, float value);

	static sf::Vector2f lerpVector(sf::Vector2f a, sf::Vector2f b, float value);
};

