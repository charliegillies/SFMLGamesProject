#include "PlayerShipNode.h"
#include "Game.h"
#include "math.h"
#include "EventTags.h"
#include "PlayerLostLifeEvent.h"
#include "NodeFactory.h"
#include "CollisionEvent.h"
#include "Utils.h"

#include "CollisionMap.h"
#include "ProjectileCollisionEvent.h"
#include "PowerUpNode.h"
#include <iostream>

void PlayerShipNode::update()
{
	if (_speedPickupTime > 0)
		_speedPickupTime -= getGame()->deltaTime();
	if (_shieldPickupTime > 0)
		_shieldPickupTime -= getGame()->deltaTime();

	_mouseTargetRotation = getMouseTarget();

	_mouseLerpRot = Utils::lerpVector(_mouseLerpRot, _mouseTargetRotation,
		Utils::easeSmoothStep(0.6f, 1.0f));

	// apply rotation & movement
	applyRotation();
	applyMovement();

	// create a projectile
	if (_controlScheme->fired())
		shoot(_mouseLerpRot);
}

void PlayerShipNode::subscribeEvents()
{
	// subscribe to the collision event
	Delegate1<BaseEvent*> on_collide_event;
	on_collide_event.Bind(this, &PlayerShipNode::onCollide);
	subLocalEvent(EventTags::collided, on_collide_event);

	Delegate1<BaseEvent*> on_projectile_collide_event;
	on_projectile_collide_event.Bind(this, &PlayerShipNode::onProjectileCollide);
	subLocalEvent(EventTags::projectileCollision, on_projectile_collide_event);
}

void PlayerShipNode::render()
{
	// draw shield....
	if (_shieldPickupTime > 0)
	{
		_shieldSprite.setPosition(_transform->position);
		_shieldSprite.setRotation(_transform->rotation);
		getGame()->draw(_shieldSprite);
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

	getGame()->addSceneNode(proj_builder->build(gun1, dir, _transform->rotation));
	getGame()->addSceneNode(proj_builder->build(gun2, dir, _transform->rotation));
}

void PlayerShipNode::start()
{
	_controlScheme = getGame()->getControlScheme();
	_transform = static_cast<TransformNode*>(getParent()->getNode(NodeTag::transform_node));
	_collision = static_cast<CollisionNode*>(getParent()->getNode(NodeTag::collision_node));

	// Send out 'player lost life' event
	invokeGlobalEvent(EventTags::playerLostLife, new PlayerLostLifeEvent(_remainingLives));

	// start at mouse rot
	_mouseTargetRotation = getMouseTarget();
	_mouseLerpRot = _mouseTargetRotation;
	applyRotation();

	// assign bounds
	_topLeftMovementBound = _transform->origin;
	_botRightMovementBound = sf::Vector2f(
		CollisionMap::width * CollisionMap::cellSize,
		CollisionMap::height * CollisionMap::cellSize) - _topLeftMovementBound;

	// load shield sprite
	sf::Texture& shield_txr = getGame()->getTexture("Sprites//shield.png");
	shield_txr.setSmooth(true);
	_shieldSprite.setTexture(shield_txr);
	// set origin to .5 of the txr
	auto size = shield_txr.getSize();
	_shieldSprite.setOrigin(size.x / 2, size.y / 2);
}

void PlayerShipNode::onCollide(BaseEvent* e)
{
	CollisionEvent* collision = static_cast<CollisionEvent*>(e);
	assert(collision != nullptr);

	CollisionNode* collider = collision->collider_b;

	// test if the collider is an obstacle, if so - we need to stop moving..
	if ((collider->categoryBits & CollisionNode::OBSTACLE_MASK) != 0)
	{
		// move back to where we were
		_transform->position -= _lastMovement;
	}

	if ((collider->categoryBits & CollisionNode::PICKUP_MASK) != 0)
	{
		// get the pickup node....
		PowerUpNode* power_up = static_cast<PowerUpNode*>(collider->getParent()->getNode(NodeTag::powerup_node));
		applyPowerup(power_up);
	}
}

void PlayerShipNode::onProjectileCollide(BaseEvent* e)
{
	ProjectileCollisionEvent* projectileCollision = static_cast<ProjectileCollisionEvent*>(e);
	
	_remainingLives--;
	// handle this better, but for now...
	onLifeChanged();
}

void PlayerShipNode::applyPowerup(PowerUpNode* power_up)
{
	const float pickup_time = 3.0f;

	switch (power_up->Pickup)
	{
		case PICKUP_SHIELD: 
			_shieldPickupTime = pickup_time;
			getGame()->removeSceneNode(power_up->getParent());
			break;
		
		case PICKUP_HEALTH: 
			if (_remainingLives != max_lives)
			{
				// add 1 life from the pick up
				_remainingLives += 1;
				// broadcast event
				onLifeChanged();
				// destroy the power up
				getGame()->removeSceneNode(power_up->getParent());
			}

			break;
		
		case PICKUP_SPEED: 
			_speedPickupTime = pickup_time;
			getGame()->removeSceneNode(power_up->getParent());
			break;
	}
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
	float speed = 240.0f;

	// check if the speed modifier applies
	if (_speedPickupTime > 0)
		speed *= 1.5f;

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
	sf::Vector2f pre_move_pos = _transform->position;
	sf::Vector2f pos = _transform->position + velocity;

	// make sure we're in bounds
	pos.x = Utils::clamp(pos.x, _topLeftMovementBound.x, _botRightMovementBound.x);
	pos.y = Utils::clamp(pos.y, _topLeftMovementBound.y, _botRightMovementBound.y);

	_transform->position = pos;
	_lastMovement = pos - pre_move_pos;
}

void PlayerShipNode::applyRotation()
{
	float angle = Utils::radToDeg(atan2(_mouseLerpRot.y, _mouseLerpRot.x));
	angle += 90;
	_transform->rotation = angle;
}

void PlayerShipNode::onLifeChanged()
{
	PlayerLostLifeEvent lost_life_event(_remainingLives);
	invokeGlobalEvent(EventTags::playerLostLife, &lost_life_event);
}