#pragma once
#include "StateTransition.h"

/*
	Judges if the player is in distance of the state holders transform.
*/
class PlayerInDistanceCondition : public StateTransition
{
public:
	explicit PlayerInDistanceCondition(float dst) : _distance(dst) { }
	
	~PlayerInDistanceCondition();

	bool conditionMet(StateMachineNode* stateMachine) override;

private:
	float _distance;
};