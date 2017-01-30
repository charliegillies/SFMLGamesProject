#include "PlayerLivesUINode.h"
#include "EventTags.h"
#include "BaseEvent.h"
#include "PlayerLostLifeEvent.h"
#include "Game.h"

PlayerLivesUINode::PlayerLivesUINode()
{
	_hpIcon = new ImageNode(8, 5, "Sprites//ui//playerLife1_blue.png");
	_hpStatusBar = new StatusBar(
		"Sprites//ui//barHorizontal_green_left.png", 
		"Sprites//ui//barHorizontal_green_mid.png", 
		"Sprites//ui//barHorizontal_green_right.png", 45, 5, 100);

	_energyIcon = new ImageNode(170, 5, "Sprites//ui//energy_icon.png");
	_energyStatusBar = new StatusBar(
		"Sprites//ui//barHorizontal_yellow_left.png",
		"Sprites//ui//barHorizontal_yellow_mid.png",
		"Sprites//ui//barHorizontal_yellow_right.png", 200, 5, 100);

	_enemyText = new TextNode(330, 5, "Fonts//kenvector_future.ttf", "ENEMIES: 0", sf::Color::White, 20);
}

PlayerLivesUINode::~PlayerLivesUINode() {}

void PlayerLivesUINode::start()
{
	addChild(_hpStatusBar);
	addChild(_hpIcon);

	addChild(_energyStatusBar);
	addChild(_energyIcon);

	addChild(_enemyText);

	//initialise all child nodes
	SceneNode::start();
}

void PlayerLivesUINode::subscribeEvents()
{
	// create a delegate, bind this object to the onPlayerLostLife method call
	Delegate1<BaseEvent*> life_lost_event;
	life_lost_event.Bind(this, &PlayerLivesUINode::onPlayerLostLife);
	// subscribe to the global event
	subGlobalEvent(EventTags::playerLostLife, life_lost_event);

	Delegate1<BaseEvent*> eEnemyReg;
	eEnemyReg.Bind(this, &PlayerLivesUINode::onEnemyRegister);
	subGlobalEvent(EventTags::registerEnemy, eEnemyReg);

	Delegate1<BaseEvent*> eEnemyUnreg;
	eEnemyUnreg.Bind(this, &PlayerLivesUINode::onEnemyUnregister);
	subGlobalEvent(EventTags::unregisterEnemy, eEnemyUnreg);
}

void PlayerLivesUINode::onPlayerLostLife(BaseEvent* e)
{
	// attempt convert, assert that it is not null
	PlayerLostLifeEvent* lost_life_event = static_cast<PlayerLostLifeEvent*>(e);
	assert(lost_life_event != nullptr);

	_hpStatusBar->setBarPerc(lost_life_event->hp_percentage);
	_energyStatusBar->setBarPerc(lost_life_event->energy_percentage);
}

void PlayerLivesUINode::onEnemyRegister(BaseEvent* e)
{
	_aliveEnemies++;

	_enemyText->setText("ENEMIES: " + to_string(_aliveEnemies));
}

void PlayerLivesUINode::onEnemyUnregister(BaseEvent* e)
{
	_aliveEnemies--;

	_enemyText->setText("ENEMIES: " + to_string(_aliveEnemies));
}
