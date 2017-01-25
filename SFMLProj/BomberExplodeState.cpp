#include "BomberExplodeState.h"
#include <iostream>

BomberExplodeState::BomberExplodeState(float range) 
	: range(range) { }

BomberExplodeState::~BomberExplodeState() { }

void BomberExplodeState::onEnter() { }

void BomberExplodeState::execute()
{
	// Begin playing the animation?

	// Get everyone within our range using raycasts, damage them!


}

void BomberExplodeState::onExit()
{
	
}