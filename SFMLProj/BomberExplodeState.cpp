#include "BomberExplodeState.h"
#include "NodeFactory.h"
#include "Utils.h"
#include "RaycastUtility.h"
#include "EventTags.h"
#include "ProjectileCollisionEvent.h"

BomberExplodeState::BomberExplodeState(float range) 
	: range(range) { }

BomberExplodeState::~BomberExplodeState() { }

void BomberExplodeState::onEnter()
{
	auto pos = stateMachine->nTransform->position;

	// raycast towards the player, if we hit him - we can damage him.
	auto ray_dir = Utils::normalize((stateMachine->playerTransform->position - pos));
	auto raycast = stateMachine->nCollider->raycast(pos, ray_dir, range, 
		CollisionNode::OBSTACLE_MASK | CollisionNode::PLAYER_MASK);

	// check if we hit the player
	if (raycast.hit && (raycast.collider->categoryBits & CollisionNode::PLAYER_MASK) != 0)
	{
		raycast.collider->invokeLocalEvent(EventTags::projectileCollision, 
			new ProjectileCollisionEvent(40));
	}

	// create an explosion where we were standing, delete ourselves from the hierachy
	stateMachine->createSceneNode(NodeFactory::createSonicExplosion(pos.x, pos.y));
	stateMachine->removeSceneNode(stateMachine->getParent());
}

void BomberExplodeState::execute() { }

void BomberExplodeState::onExit() { }
