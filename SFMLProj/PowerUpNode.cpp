#include "PowerUpNode.h"

PowerUpNode::PowerUpNode(PickupType pickup) 
	: Pickup(pickup) { }

PowerUpNode::~PowerUpNode() { }

string PowerUpNode::getNodeTag()
{
	return NodeTag::powerup_node;
}