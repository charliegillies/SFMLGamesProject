#include "PlayerShipNode.h"
#include "Game.h"
#include "math.h"
#include "EventTags.h"
#include "PlayerLostLifeEvent.h"
#include "CollisionEvent.h"
#include "Utils.h"

#include "CollisionMap.h"
#include "ProjectileCollisionEvent.h"
#include "PowerUpNode.h"

void PlayerShipNode::update()
{
	if (isShieldUp())
	{
		// defines how much the shield will degrade per second it's held down
		const float shield_degrade = 40;
		// multiply by dt to ensure it degrades by time
		_shieldHpNode->damage(shield_degrade * getGame()->deltaTime());
		// shield status changed, tell everyone about it
		broadcastStatusChange();
	}

	// if pickups are active, decrease time
	if (_speedPickupTime > 0)
		_speedPickupTime -= getGame()->deltaTime();

	_mouseTargetRotation = getMouseTarget();

	_mouseLerpRot = Utils::lerpVector(_mouseLerpRot, _mouseTargetRotation,
		Utils::easeSmoothStep(0.6f, 1.0f));

	// apply rotation & movement
	applyRotation();
	applyMovement();

	// create a projectile
	if (_controlScheme->primaryFired())
		shootPrimary(_mouseLerpRot);
	else if (_controlScheme->secondaryFired())
		shootSecondary(_mouseLerpRot);

	// update children
	SceneNode::update();
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
	if (_shieldUp)
	{
		_shieldSprite.setPosition(_transform->position);
		_shieldSprite.setRotation(_transform->rotation);
		getGame()->draw(_shieldSprite);
	}
}

void PlayerShipNode::shootPrimary(sf::Vector2f dir)
{
	if (primaryFire->onCooldown()) return;

	sf::Vector2f ship_pos = _transform->position;

	// transform the points by rotation, fire
	sf::Transform sf_transform; 
	sf_transform.rotate(_transform->rotation);
	sf::Vector2f gun1 = ship_pos + sf_transform.transformPoint(-20, -40);
	sf::Vector2f gun2 = ship_pos + sf_transform.transformPoint(20, -40);

	getGame()->addSceneNode(primaryFire->builder->build(gun1, dir, _transform->rotation));
	getGame()->addSceneNode(primaryFire->builder->build(gun2, dir, _transform->rotation));
	primaryFire->onShoot();

	primaryAudioNode->trigger();
}

void PlayerShipNode::shootSecondary(sf::Vector2f dir)
{
	if (secondaryFire->onCooldown()) return;

	sf::Vector2f ship_pos = _transform->position;

	// transform the points by rotation, fire
	sf::Transform sf_transform;
	sf_transform.rotate(_transform->rotation);
	sf::Vector2f spawn_pos = ship_pos + sf_transform.transformPoint(0, -60);

	getGame()->addSceneNode(secondaryFire->builder->build(spawn_pos, dir, _transform->rotation));
	secondaryFire->onShoot();

	secondaryAudioNode->trigger();
}

void PlayerShipNode::start()
{
	_controlScheme = getGame()->getControlScheme();
	_transform = static_cast<TransformNode*>(getParent()->getNode(NodeTag::transform_node));
	_collision = static_cast<CollisionNode*>(getParent()->getNode(NodeTag::collision_node));
	_hpNode = static_cast<HealthNode*>(getParent()->getNode(NodeTag::health_node));

	// create the shield hp node
	_shieldHpNode = new HealthNode(100);

	// Send out 'player lost life' event
	broadcastStatusChange();

	// start at mouse rot
	_mouseTargetRotation = getMouseTarget();
	_mouseLerpRot = _mouseTargetRotation;
	applyRotation();

	// assign bounds
	_topLeftMovementBound = _transform->origin;
	_botRightMovementBound = sf::Vector2f(CollisionMap::width * CollisionMap::cellSize,
		CollisionMap::height * CollisionMap::cellSize) - _topLeftMovementBound;

	// load shield sprite
	sf::Texture& shield_txr = getGame()->getTexture("Sprites//player//shield.png");
	shield_txr.setSmooth(true);
	_shieldSprite.setTexture(shield_txr);
	// set origin to .5 of the txr
	auto size = shield_txr.getSize();
	_shieldSprite.setOrigin(size.x / 2, size.y / 2);

	addChild(primaryFire);
	addChild(secondaryFire);
	addChild(primaryAudioNode);
	addChild(secondaryAudioNode);

	SceneNode::start();
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
	auto* proj_col_event = static_cast<ProjectileCollisionEvent*>(e);


	if (isShieldUp())
	{
		_shieldHpNode->damage(5);

		isShieldUp(); // evaluate condition again
	}
	else
		_hpNode->damage(proj_col_event->damageOnHit);

	broadcastStatusChange();
}

void PlayerShipNode::applyPowerup(PowerUpNode* power_up)
{
	const float pickup_time = 3.0f;

	switch (power_up->Pickup)
	{
		case PickupType::PICKUP_SHIELD: 
			if (!_shieldHpNode->atFullHP())
			{
				_shieldHpNode->heal(25);
				getGame()->removeSceneNode(power_up->getParent());
			}

			break;
		
		case PickupType::PICKUP_HEALTH: 
			if (!_hpNode->atFullHP())
			{
				_hpNode->heal(25);
				// broadcast event
				broadcastStatusChange();
				// destroy the power up
				getGame()->removeSceneNode(power_up->getParent());
			}

			break;
		
		case PickupType::PICKUP_SPEED: 
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
	float speed = 360.0f;

	// check if the speed modifier applies
	if (_speedPickupTime > 0)
		speed *= 1.5f;

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

void PlayerShipNode::broadcastStatusChange()
{
	PlayerLostLifeEvent lost_life_event(_hpNode->getPercentageHP(), _shieldHpNode->getPercentageHP());
	invokeGlobalEvent(EventTags::playerLostLife, &lost_life_event);
}

bool PlayerShipNode::isShieldUp()
{
	_shieldUp = (_controlScheme->shieldUp() && !_shieldHpNode->isDead());
	return _shieldUp;
}