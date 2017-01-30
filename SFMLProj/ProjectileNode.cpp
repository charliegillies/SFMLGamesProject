#include "ProjectileNode.h"
#include "EventTags.h"
#include "CollisionEvent.h"
#include "CollisionNode.h"
#include "ProjectileCollisionEvent.h"
#include "AudioNode.h"

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

	if (onDeathCreateFunc != nullptr)
	{
		// get transform
		TransformNode* transform = static_cast<TransformNode*>(getParent()->getNode(NodeTag::transform_node));
		// invoke the creator function
		SceneNode* created = onDeathCreateFunc(transform->position.x, transform->position.y);
		getGame()->addSceneNode(created);
	}

	if (audio_hit_fp != "")
		getGame()->addSceneNode(new AudioNode(AudioPlayMode::PLAY_ONCE_DESTROY_SELF, audio_hit_fp));

	// now delete self
	getGame()->removeSceneNode(getParent());
}