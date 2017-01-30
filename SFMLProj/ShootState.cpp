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

	if (audio_node == nullptr)
		audio_node = static_cast<AudioNode*>(stateMachine->
			getParent()->getNode(NodeTag::audio_node));
}

void ShootState::execute()
{
	auto transform = stateMachine->nTransform;

	sf::Vector2f dir = (stateMachine->playerTransform->position - transform->position);
	dir = Utils::normalize(dir);

	shoot(transform, dir);

	if (audio_node != nullptr)
		audio_node->trigger();

	projectile_data_node->onShoot();
}

void ShootState::shoot(TransformNode* transform, sf::Vector2f dir)
{
	// figure out where we're supposed to spawn the projectile
	sf_transform.rotate(transform->rotation);
	sf::Vector2f pos = transform->position + sf_transform.transformPoint(0, 22.5f);

	// construct a projectile to shoot
	SceneNode* projectile = projectile_data_node->builder->build(pos, dir, transform->rotation);
	stateMachine->createSceneNode(projectile);
}

void ShootState::onExit()
{
}