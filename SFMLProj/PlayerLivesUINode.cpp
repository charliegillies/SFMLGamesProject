#include "PlayerLivesUINode.h"
#include "EventTags.h"
#include "BaseEvent.h"
#include "PlayerLostLifeEvent.h"
#include "Game.h"

PlayerLivesUINode::PlayerLivesUINode()
{
	// instantiating this here instead of start() means that we won't have
	// issues with the execution order with events.
	_lifeCounterText = new TextNode(10, 5, "Fonts//kenvector_future.ttf",
		"0", sf::Color::White, 30);
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
	// create a delegate, bind this object to the onPlayerLostLife method call
	Delegate1<BaseEvent*> life_lost_event;
	life_lost_event.Bind(this, &PlayerLivesUINode::onPlayerLostLife);

	// subscribe to the global event
	addGlobalEventReceiver(EventTags::playerLostLife, life_lost_event);
}

void PlayerLivesUINode::onPlayerLostLife(BaseEvent* e)
{
	// attempt convert, assert that it is not null
	PlayerLostLifeEvent* lost_life_event = static_cast<PlayerLostLifeEvent*>(e);
	assert(lost_life_event != nullptr);

	// we do this to avoid issues with execution order
	_lifeCounterText->setText(to_string(lost_life_event->remainingLives));
}