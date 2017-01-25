#include "ProjectileBuilder.h"
#include "VelocityNode.h"
#include "CollisionNode.h"
#include "ProjectileNode.h"
#include "DestroyAfterTimeNode.h"
#include "SpriteNode.h"

ProjectileBuilder::ProjectileBuilder(string texture_path, flag col_flag, float lifeTime, float speed, float dmg, float radius)
	: txr_fp(texture_path), destroy_time(lifeTime), speed(speed), 
		radius(radius), dmg(dmg), collision_flag(col_flag), _creatorPtr(nullptr) { }

ProjectileBuilder::~ProjectileBuilder() { }

SceneNode* ProjectileBuilder::build(sf::Vector2f position, sf::Vector2f direction, float rot)
{
	SceneNode* base_node = new SceneNode();

	// sprite node
	base_node->addChild(new SpriteNode(txr_fp));

	// position, rotation, origin node
	TransformNode* transform_node = new TransformNode();
	transform_node->position = position;
	transform_node->origin = sf::Vector2f(4, 18);
	transform_node->rotation = rot;
	base_node->addChild(transform_node);

	// destroy after 2.5 seconds
	base_node->addChild(new DestroyAfterTimeNode(destroy_time));

	auto proj_node = new ProjectileNode(dmg);
	proj_node->onDeathCreateFunc = _creatorPtr;
	base_node->addChild(proj_node);

	// setup collider
	CollisionNode* collider = new CollisionNode(radius);
	collider->setFlags(CollisionNode::PROJECTILE_MASK, collision_flag);
	base_node->addChild(collider);

	// movement node
	base_node->addChild(new VelocityNode(speed, direction));

	return base_node;
}

void ProjectileBuilder::setCreatorPtr(objCreatorPtr creatorPtr)
{
	this->_creatorPtr = creatorPtr;
}