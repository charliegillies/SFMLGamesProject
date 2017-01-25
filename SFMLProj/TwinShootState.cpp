#include "TwinShootState.h"

TwinShootState::TwinShootState() { }
TwinShootState::~TwinShootState() { }

void TwinShootState::shoot(TransformNode* transform, sf::Vector2f dir)
{
	// figure out where we're supposed to spawn the projectile
	sf_transform.rotate(transform->rotation);
	sf::Vector2f gun1 = transform->position + sf_transform.transformPoint(30, 22.5f);
	sf::Vector2f gun2 = transform->position + sf_transform.transformPoint(-30, 22.5f);

	// construct a projectile to shoot
	SceneNode* projectile = projectile_data_node->builder->build(gun1, dir, transform->rotation);
	stateMachine->createSceneNode(projectile);

	// construct a projectile to shoot
	projectile = projectile_data_node->builder->build(gun2, dir, transform->rotation);
	stateMachine->createSceneNode(projectile);
}