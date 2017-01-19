#include "PlayerShipNode.h"
#include "Game.h"
#include "math.h"
#include "EventTags.h"
#include "PlayerLostLifeEvent.h"
#include "NodeFactory.h"
#include "CollisionEvent.h"
#include "Utils.h"

#include "RaycastUtility.h"

void PlayerShipNode::update()
{
	// also handles rotation
	sf::Vector2f dir = handleMovement();

	cast = _collision->raycast(_transform->position, dir, 500.0f, 
		CollisionNode::ENEMY_MASK | CollisionNode::OBSTACLE_MASK);

	getGame()->setDebugValue("player dir", to_string(dir.x) + "," + to_string(dir.y));

	// create a projectile
	if (_controlScheme->fired())
		shoot(dir);
}

void PlayerShipNode::render()
{
	_collision->drawCast(cast);

	shape_ray_int_1.setPosition(cast.start);
	shape_ray_int_2.setPosition(cast.end);
	getGame()->draw(shape_ray_int_1);
	getGame()->draw(shape_ray_int_2);

	if (cast.hit)
	{
		shape_ray_int_1.setPosition(cast.intersect_1);
		shape_ray_int_2.setPosition(cast.intersect_2);
		getGame()->draw(shape_ray_int_1);
		getGame()->draw(shape_ray_int_2);
	}
}

void PlayerShipNode::shoot(sf::Vector2f dir)
{
	sf::Vector2f ship_pos = _transform->position;

	// transform the points by rotation, fire
	sf::Transform sf_transform; 
	sf_transform.rotate(_transform->rotation);
	sf::Vector2f gun1 = ship_pos + sf_transform.transformPoint(-20, 15);
	sf::Vector2f gun2 = ship_pos + sf_transform.transformPoint(20, 15);

	getGame()->addSceneNode(NodeFactory::createShipProjectile(
		gun1, dir, 400, _transform->rotation));

	getGame()->addSceneNode(NodeFactory::createShipProjectile(
		gun2, dir, 400, _transform->rotation));
}

void PlayerShipNode::start()
{
	_controlScheme = getGame()->getControlScheme();
	_transform = static_cast<TransformNode*>(getParent()->getNode(NodeTag::transform_node));
	_collision = static_cast<CollisionNode*>(getParent()->getNode(NodeTag::collision_node));

	// Send out 'player lost life' event
	invokeGlobalEvent(EventTags::playerLostLife, new PlayerLostLifeEvent(3));

	// subscribe to the collision event
	Delegate1<BaseEvent*> on_collide_event;
	on_collide_event.Bind(this, &PlayerShipNode::onCollide);
	subLocalEvent(EventTags::collided, on_collide_event);
}

void PlayerShipNode::onCollide(BaseEvent* e)
{
	CollisionEvent* collision = static_cast<CollisionEvent*>(e);
	assert(collision != nullptr);

	SceneNode* collider = collision->collider;

}

sf::Vector2f PlayerShipNode::rotateToMouse()
{
	// get mouse and ship position
	auto mousePos = getGame()->getCamera()->getWorldMouse();
	auto pos = _transform->position;
	// rotate towards mouse
	auto angle = Utils::calcAngle(mousePos, pos);
	angle += 90; // sprite doesn't face right, quick fix
	_transform->rotation = angle;

	sf::Vector2f s = mousePos - pos;
	return Utils::normalize(s);
}

sf::Vector2f PlayerShipNode::handleMovement()
{
	const float speed = 240.0f;

	// rotate towards the mouse
	sf::Vector2f direction = rotateToMouse();
	sf::Vector2f velocity(0, 0);

	if (_controlScheme->forwards())
		velocity = direction*speed;
	else if (_controlScheme->backwards())
	{
		velocity = direction*(speed / 2);
		velocity = -velocity;
	}

	velocity *= getGame()->deltaTime();
	_transform->position += velocity;

	return direction;
}