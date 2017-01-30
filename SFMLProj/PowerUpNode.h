#pragma once
#include "SceneNode.h"

enum class PickupType
{
	PICKUP_SHIELD = 0,
	PICKUP_HEALTH = 1,
	PICKUP_SPEED = 2
};

/*
	Simple composite class that represents a "power up"
	and has a specific node tag for the player to find it.
*/
class PowerUpNode : public SceneNode
{
public:
	explicit PowerUpNode(PickupType pickup);
	~PowerUpNode();

	string getNodeTag() override;

	void onRemoved() override;

	PickupType Pickup;
};