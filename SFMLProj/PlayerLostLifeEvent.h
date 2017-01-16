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
	// the number of remaining lives that the player has
	int remainingLives;

	explicit PlayerLostLifeEvent(int lives) : remainingLives(lives) {};
	~PlayerLostLifeEvent() {}
};