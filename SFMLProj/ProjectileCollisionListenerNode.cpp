#include "ProjectileCollisionListenerNode.h"
#include "EventTags.h"
#include "ProjectileCollisionEvent.h"
#include "Game.h"

ProjectileCollisionListenerNode::ProjectileCollisionListenerNode() { }
ProjectileCollisionListenerNode::~ProjectileCollisionListenerNode() { }

void ProjectileCollisionListenerNode::start()
{
	hp_node = static_cast<HealthNode*>(getParent()->getNode(NodeTag::health_node));
	assert(hp_node != nullptr);
}

void ProjectileCollisionListenerNode::subscribeEvents()
{
	// bind onProjectileCollide to the projectile collision event.
	Delegate1<BaseEvent*> proj_collider_del;
	proj_collider_del.Bind(this, &ProjectileCollisionListenerNode::onProjectileCollide);
	subLocalEvent(EventTags::projectileCollision, proj_collider_del);
}

void ProjectileCollisionListenerNode::onProjectileCollide(BaseEvent* proj_collision)
{
	// get the projectile collision event
	auto proj_collision_event = static_cast<ProjectileCollisionEvent*>(proj_collision);
	// damage our local health node
	hp_node->damage(proj_collision_event->damageOnHit);

	// remove self if dead.. we may want to rethink this, or at least broadcast a local event.
	if (hp_node->isDead())
		getGame()->removeSceneNode(getParent());
}