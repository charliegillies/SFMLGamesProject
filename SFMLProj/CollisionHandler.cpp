#include "CollisionHandler.h"
#include "RegisterColliderEvent.h"
#include "EventTags.h"

CollisionHandler::CollisionHandler() 
	: _allColliders(), _collisionMap(&_allColliders) { }

CollisionHandler::~CollisionHandler() { }

void CollisionHandler::update()
{
	_collisionMap.buildMap();

	CheckMap check_map{};

	// test all possible collisions
	for (int x = 0; x < CollisionMap::width; x++)
	{
		for (int y = 0; y < CollisionMap::height; y++)
		{
			// get the test nodes in this cell
			vector<CollisionNode*> cell_nodes = _collisionMap.getCollidersInCell(x, y);

			// without even 2 elements, don't bother testing..
			if (cell_nodes.size() < 2) continue;

			// check for potential collisions inside of this cell
			checkPotentialCollisions(check_map, cell_nodes);
		}
	}
}

void CollisionHandler::checkPotentialCollisions(CheckMap& check_map, vector<CollisionNode*>& cell_nodes)
{
	// we have more than 2 potential colliders, let's find out..
	for (auto i = cell_nodes.begin(); i != cell_nodes.end(); ++i)
	{
		CollisionNode* a = (*i);

		for (auto j = (i + 1); j != cell_nodes.end(); ++j)
		{
			CollisionNode* b = (*j);

			const string aHash = to_string(a->getID()) + ":" + to_string(b->getID());
			const string bHash = to_string(b->getID()) + ":" + to_string(a->getID());

			// check we haven't checked this collision before, if we have - skip
			if (check_map[aHash] || check_map[bHash]) continue;

			check_map[aHash] = true;
			check_map[bHash] = true;

			if (a->collides(b))
			{
				// notify a and b that we have collided
				a->onCollide(b);
				b->onCollide(a);
			}
		}
	}
}

void CollisionHandler::subscribeEvents()
{
	Gallant::Delegate1<BaseEvent*> collision_register;
	collision_register.Bind(this, &CollisionHandler::onColliderRegister);
	subGlobalEvent(EventTags::registerCollider, collision_register);
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