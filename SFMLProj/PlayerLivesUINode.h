#pragma once
#include "SceneNode.h"
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

	void update() override;
	void start() override;
	void subscribeEvents() override;

	// function that is passed in for the player lost life event
	void onPlayerLostLife(BaseEvent* e);
private:
	TextNode* _lifeCounterText;
};

