#pragma once
#include "SceneNode.h"
#include "EventTags.h"

/*
 * Registers itself as an enemy inside of Start().
 * Unregisters itself when removed().
 */
class RegisterEnemyNode : public SceneNode
{
public:
	RegisterEnemyNode() { }
	~RegisterEnemyNode() { }

	void onRemoved() override
	{
		// this event does not need an event param
		invokeGlobalEvent(EventTags::unregisterEnemy, nullptr);
	}

	void start() override
	{
		// this event does not need an event param
		invokeGlobalEvent(EventTags::registerEnemy, nullptr);
	}
};

