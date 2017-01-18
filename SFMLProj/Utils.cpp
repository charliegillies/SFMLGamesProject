#include "Utils.h"
#include <math.h>

float Utils::clamp(float value, float min, float max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;

	return value;
}

float Utils::lerpSmoothStep(float currentTime, float lerpTime)
{
	float t = currentTime / lerpTime;
	return t * t * (3.0f - 2.0f * t);
}

sf::Vector2f Utils::normalize(sf::Vector2f source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}