#pragma once
#include "SceneNode.h"

/*
 * Listens for changes in the game state in order to change scenes.
 * 
 * Listens for enemies registering (when they're created) and 
 * enemies unregistering (when they're destroyed).
 * 
 * On all enemies dying, game state is 'won'. 
 * On player dying, game state is 'lost'.
 */
class GameStateListener : public SceneNode
{
public:
	GameStateListener();
	~GameStateListener();

	void subscribeEvents() override;
	void update() override;

private:
	// called on the player dying
	void onPlayerDeath(BaseEvent* e);
	// called on an enemy registering
	void onEnemyRegister(BaseEvent* e);
	// called on an enemy dying
	void onEnemyUnregister(BaseEvent* e);

	int _aliveEnemies;
	bool _playerDead;
};
