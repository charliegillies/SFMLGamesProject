#include "PowerUpNode.h"
#include "Game.h"
#include "AudioNode.h"

PowerUpNode::PowerUpNode(PickupType pickup) 
	: Pickup(pickup) { }

PowerUpNode::~PowerUpNode() { }

string PowerUpNode::getNodeTag()
{
	return NodeTag::powerup_node;
}

void PowerUpNode::onRemoved()
{
	// Create sfx of pickup
	getGame()->addSceneNode(new AudioNode(AudioPlayMode::PLAY_ONCE_DESTROY_SELF, "Sfx//pickup.wav"));
}
