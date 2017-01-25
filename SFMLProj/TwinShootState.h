#pragma once
#include "ShootState.h"

/*
	Shoots two bullets for the price of one.
*/
class TwinShootState : public ShootState
{
public:
	TwinShootState();
	~TwinShootState();

	void shoot(TransformNode* transform, sf::Vector2f dir) override;
};