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

	static float lerpSmoothStep(float currentTime, float lerpTime);
};

