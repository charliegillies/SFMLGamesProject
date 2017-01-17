#pragma once
#include "SceneNode.h"

/*
	Scene node that is responsible for keeping the 
	player up to date on how many lives they have remaining.
*/
class PlayerLivesUINode : SceneNode
{
public:
	PlayerLivesUINode();
	~PlayerLivesUINode();

	void update() override;
	void start() override;
};

