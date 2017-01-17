#include "PlayerLivesUINode.h"
#include "EventTags.h"
#include "BaseEvent.h"
#include "Game.h"
#include "PlayerLostLifeEvent.h"

PlayerLivesUINode::PlayerLivesUINode()
{
	_lifeCounterText = new TextNode(10, 5, "Fonts//kenvector_future.ttf",
		"DEBUG TEXT", sf::Color::White, 36);
}

PlayerLivesUINode::~PlayerLivesUINode() {}

void PlayerLivesUINode::start()
{
	// create a text node 
	addChild(_lifeCounterText);

	//initialise all child nodes
	SceneNode::start();
}

void PlayerLivesUINode::subscribeEvents()
{
	Delegate1<BaseEvent*> del;
	del.Bind(this, &PlayerLivesUINode::onPlayerLostLife);
	addGlobalEventReceiver(EventTags::playerLostLife, del);
}

void PlayerLivesUINode::onPlayerLostLife(BaseEvent* e)
{
	// attempt convert, assert that it is not null
	PlayerLostLifeEvent* lost_life_event = static_cast<PlayerLostLifeEvent*>(e);
	assert(lost_life_event != nullptr);

	// we do this to avoid issues with execution order
	_lifeCounterText->setText(std::to_string(lost_life_event->remainingLives));
}