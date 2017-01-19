#include "ProjectileNode.h"
#include "EventTags.h"
#include "CollisionEvent.h"
#include "CollisionNode.h"
#include "ProjectileCollisionEvent.h"

void ProjectileNode::subscribeEvents()
{
	Delegate1<BaseEvent*> del;
	del.Bind(this, &ProjectileNode::onCollide);
	subLocalEvent(EventTags::collided, del);
}

void ProjectileNode::onCollide(BaseEvent* event)
{
	CollisionEvent* collision = static_cast<CollisionEvent*>(event);
	assert(collision != nullptr);

	// notify the person we collided with....
	collision->collider_b->invokeLocalEvent(EventTags::projectileCollision,
		new ProjectileCollisionEvent(dmg));

	// now delete self
	getGame()->removeSceneNode(getParent());
}