#pragma once
#include "SceneNode.h"
#include "ImageNode.h"
#include "StatusBar.h"
#include "TextNode.h"

/*
	Scene node that is responsible for keeping the 
	player up to date on how many lives they have remaining.
*/
class PlayerLivesUINode : public SceneNode
{
public:
	PlayerLivesUINode();
	~PlayerLivesUINode();

	void start() override;
	void subscribeEvents() override;

	// function that is passed in for the player lost life event
	void onPlayerLostLife(BaseEvent* e);
	void onEnemyRegister(BaseEvent* e);
	void onEnemyUnregister(BaseEvent* e);

private:
	int _aliveEnemies;

	ImageNode* _hpIcon;
	StatusBar* _hpStatusBar;
	
	ImageNode* _energyIcon;
	StatusBar* _energyStatusBar;

	TextNode* _enemyText;
};