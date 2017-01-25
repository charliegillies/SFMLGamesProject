#include "BomberExplodeState.h"
#include <iostream>
#include "NodeFactory.h"

BomberExplodeState::BomberExplodeState(float range) 
	: range(range) { }

BomberExplodeState::~BomberExplodeState() { }

void BomberExplodeState::onEnter()
{
	auto pos = stateMachine->nTransform->position;

	stateMachine->createSceneNode(NodeFactory::createPixelExplosion(pos.x, pos.y));
	stateMachine->removeSceneNode(stateMachine->getParent());

	// raycast & damage everyone we hit...


}

void BomberExplodeState::execute() { }

void BomberExplodeState::onExit() { }
