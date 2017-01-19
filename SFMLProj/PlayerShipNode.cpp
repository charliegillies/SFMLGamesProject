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
	_mouseTargetRotation = getMouseTarget();

	_mouseLerpRot = Utils::lerpVector(_mouseLerpRot, _mouseTargetRotation,
		Utils::easeSmoothStep(0.5f, 1.0f));

	// apply rotation & movement
	applyRotation();
	applyMovement();

	getGame()->setDebugValue("rot", to_string(_transform->rotation));
	getGame()->setDebugValue("cur rot", to_string(_mouseLerpRot.x) + " , " + to_string(_mouseLerpRot.y));
	getGame()->setDebugValue("des rot", to_string(_mouseTargetRotation.x) + " , " + to_string(_mouseTargetRotation.y));

	cast = _collision->raycast(_transform->position, _mouseLerpRot, 500.0f, 
		CollisionNode::ENEMY_MASK | CollisionNode::OBSTACLE_MASK);

	// create a projectile
	if (_controlScheme->fired())
		shoot(_mouseLerpRot);
}

void PlayerShipNode::render()
{
	_collision->drawCast(cast);
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

	// start at mouse rot
	_mouseTargetRotation = getMouseTarget();
	_mouseLerpRot = _mouseTargetRotation;
	applyRotation();
}

void PlayerShipNode::onCollide(BaseEvent* e)
{
	CollisionEvent* collision = static_cast<CollisionEvent*>(e);
	assert(collision != nullptr);

	SceneNode* collider = collision->collider;
}

sf::Vector2f PlayerShipNode::getMouseTarget()
{
	// get mouse and ship position
	auto mousePos = getGame()->getCamera()->getWorldMouse();
	auto pos = _transform->position;
	sf::Vector2f s = mousePos - pos;
	return Utils::normalize(s);
}

void PlayerShipNode::applyMovement()
{
	const float speed = 240.0f;

	// rotate towards the mouse
	sf::Vector2f direction = _mouseLerpRot;
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
}

void PlayerShipNode::applyRotation()
{
	float angle = Utils::radToDeg(atan2(_mouseLerpRot.y, _mouseLerpRot.x));
	angle += 90;
	_transform->rotation = angle;
}