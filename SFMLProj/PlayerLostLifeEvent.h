#pragma once
#include "BaseEvent.h"

/*
	Event is fired when a player loses his life.

	Event trigger will be the player scene node.
	Event listeners may include enemy AI or UI nodes.
*/
class PlayerLostLifeEvent : public BaseEvent
{
public:
	float hp_percentage;
	float energy_percentage;

	explicit PlayerLostLifeEvent(float hp_perc, float energy_perc) 
		: hp_percentage(hp_perc), energy_percentage(energy_perc)  {};
	
	~PlayerLostLifeEvent() {}
};