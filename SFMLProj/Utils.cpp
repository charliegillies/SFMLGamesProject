#include "Utils.h"

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