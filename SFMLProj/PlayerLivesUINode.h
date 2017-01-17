#pragma once
#include "SceneNode.h"
#include "TextNode.h"
#include "ImageNode.h"

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

private:
	TextNode* _lifeCounterText;
	ImageNode* _shipIcon;
};

