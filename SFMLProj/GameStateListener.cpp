#include "GameStateListener.h"
#include "EventTags.h"
#include "Game.h"
#include <iostream>

GameStateListener::GameStateListener() 
	: _aliveEnemies(0), _playerDead(false) { }

GameStateListener::~GameStateListener() { }

void GameStateListener::subscribeEvents()
{
	// Subscribe to all events..
	Delegate1<BaseEvent*> ePlayerDeath;
	ePlayerDeath.Bind(this, &GameStateListener::onPlayerDeath);
	subGlobalEvent(EventTags::playerDeath, ePlayerDeath);

	Delegate1<BaseEvent*> eEnemyReg;
	eEnemyReg.Bind(this, &GameStateListener::onEnemyRegister);
	subGlobalEvent(EventTags::registerEnemy, eEnemyReg);

	Delegate1<BaseEvent*> eEnemyUnreg;
	eEnemyUnreg.Bind(this, &GameStateListener::onEnemyUnregister);
	subGlobalEvent(EventTags::unregisterEnemy, eEnemyUnreg);
}

void GameStateListener::update()
{
	getGame()->setDebugValue("enemies", to_string(_aliveEnemies));

	if (_aliveEnemies <= 0)
	{
		// Game state is 'WON'
		
	}
	else if (_playerDead)
	{
		// Game state is 'LOST'

	}
}

void GameStateListener::onPlayerDeath(BaseEvent* e)
{
	_playerDead = true;
}

void GameStateListener::onEnemyRegister(BaseEvent* e)
{
	_aliveEnemies++;
}

void GameStateListener::onEnemyUnregister(BaseEvent* e)
{
	_aliveEnemies--;
}
