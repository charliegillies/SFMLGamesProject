#include "MultiCondition.h"

MultiCondition::MultiCondition(bool allTrue) : _allTrue(allTrue), _children() { }
MultiCondition::~MultiCondition() { }

bool MultiCondition::conditionMet(StateMachineNode* stateMachine)
{
	for (auto i = _children.begin(); i != _children.end(); ++i)
	{
		auto child = (*i);

		bool conditionMet = child->conditionMet(stateMachine);
		
		// we need to check inverse here!
		if (child->viewAsInverse)
			conditionMet = !conditionMet;

		// if all conditions must be met and this one didn't, we failed
		if (_allTrue && !conditionMet)
			return false;

		// if any one need to be true, and we met this condition, return true
		if (!_allTrue && conditionMet)
			return true;
	}

	return true;
}

MultiCondition* MultiCondition::addChild(StateTransition* child)
{
	_children.push_back(child);
	return this;
}