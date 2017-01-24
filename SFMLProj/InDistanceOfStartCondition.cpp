#include "InDistanceOfStartCondition.h"
#include "Utils.h"
#include "StateMachineNode.h"

InDistanceOfStartCondition::InDistanceOfStartCondition(float range) : range(range) {}
InDistanceOfStartCondition::~InDistanceOfStartCondition() {}

bool InDistanceOfStartCondition::conditionMet(StateMachineNode* stateMachine)
{
	return Utils::distance(stateMachine->nTransform->position, 
		stateMachine->startPosition) < range;
}