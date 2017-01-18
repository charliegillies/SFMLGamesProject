#include "CollisionHandler.h"
#include "RegisterColliderEvent.h"
#include "EventTags.h"

CollisionHandler::CollisionHandler() 
	: _allColliders(), _collisionMap(_allColliders) {}

CollisionHandler::~CollisionHandler() {}

void CollisionHandler::update()
{
	_collisionMap.buildMap();
}

void CollisionHandler::subscribeEvents()
{
	Gallant::Delegate1<BaseEvent*> collision_register;
	collision_register.Bind(this, &CollisionHandler::onColliderRegister);
	addGlobalEventReceiver(EventTags::registerCollider, collision_register);
}

void CollisionHandler::onColliderRegister(BaseEvent* e)
{
	// cast to register collider event and assert it was a success
	RegisterColliderEvent* register_collider = static_cast<RegisterColliderEvent*>(e);
	assert(register_collider != nullptr);
	// also ensure that the collider being registered is not null
	assert(register_collider->collider != nullptr);

	_allColliders.push_back(register_collider->collider);
}
