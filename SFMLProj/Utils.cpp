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

float Utils::easeSmoothStep(float currentTime, float lerpTime)
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

float Utils::lerp(float a, float b, float value)
{
	return a * value + b * (1 - value);
}

sf::Vector2f Utils::lerpVector(sf::Vector2f a, sf::Vector2f b, float value)
{
	sf::Vector2f lerp;
	lerp.x = Utils::lerp(a.x, b.x, value);
	lerp.y = Utils::lerp(a.y, b.y, value);
	return lerp;
}

float Utils::distance(sf::Vector2f a, sf::Vector2f b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

float Utils::calcAngle(sf::Vector2f a, sf::Vector2f b)
{
	auto angle = atan2(a.y - b.y, a.x - b.x);
	angle = angle * (180 / 3.14159265358979323846);
	return angle;
}