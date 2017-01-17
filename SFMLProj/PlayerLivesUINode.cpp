#include "PlayerLivesUINode.h"
#include "EventTags.h"
#include "BaseEvent.h"
#include "Game.h"

PlayerLivesUINode::PlayerLivesUINode() {}
PlayerLivesUINode::~PlayerLivesUINode() {}

void PlayerLivesUINode::update()
{

}

void PlayerLivesUINode::start()
{
	// create a text node 
	_lifeCounterText = new TextNode(0, 0, "Fonts//kenvector_future.ttf", 
		"0", sf::Color::White, 24);
	addChild(_lifeCounterText);



	//initialise all child nodes
	SceneNode::start();
}

void PlayerLivesUINode::subscribeEvents()
{
	//addGlobalEventReceiver(EventTags::playerLostLife, this->*onPlayerLostLife);
}

void PlayerLivesUINode::onPlayerLostLife(BaseEvent* e)
{

}