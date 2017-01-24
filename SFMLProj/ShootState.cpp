#include "ShootState.h"
#include "ProjectileDataNode.h"
#include "Utils.h"

ShootState::ShootState() : projectile_data_node(nullptr) { }
ShootState::~ShootState() { }

void ShootState::onEnter()
{
	if (projectile_data_node == nullptr)
		projectile_data_node = static_cast<ProjectileDataNode*>(
			stateMachine->getParent()->getNode(NodeTag::projectile_data_node));
}

void ShootState::execute()
{
	auto transform = stateMachine->nTransform;

	sf::Vector2f dir = (stateMachine->playerTransform->position - transform->position);
	dir = Utils::normalize(dir);

	// construct a projectile to shoot
	SceneNode* projectile = projectile_data_node->builder->build(transform->position, dir, transform->rotation);
	stateMachine->createSceneNode(projectile);

	projectile_data_node->onShoot();
}

void ShootState::onExit()
{
}