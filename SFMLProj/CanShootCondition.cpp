#include "CanShootCondition.h"
#include "ProjectileDataNode.h"

#include "StateMachineNode.h"

bool CanShootCondition::conditionMet(StateMachineNode* stateMachine)
{
	ProjectileDataNode* projectile_data_node = static_cast<ProjectileDataNode*>(
		stateMachine->getParent()->getNode(NodeTag::projectile_data_node));

	return projectile_data_node->timeTillNextShot == 0;
}

CanShootCondition::CanShootCondition()
{
}


CanShootCondition::~CanShootCondition()
{
}
