#include "PlayerInDistanceCondition.h"
#include "Utils.h"
#include "StateMachineNode.h"

PlayerInDistanceCondition::~PlayerInDistanceCondition() { }

bool PlayerInDistanceCondition::conditionMet(StateMachineNode* stateMachine)
{
	return Utils::distance(
		stateMachine->nTransform->position, 
		stateMachine->playerTransform->position) < _distance;
}