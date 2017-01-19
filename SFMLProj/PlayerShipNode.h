#pragma once
#include "SceneNode.h"
#include "ControlScheme.h"
#include "TransformNode.h"
#include "CollisionNode.h"
#include "RaycastUtility.h"

class PlayerShipNode : public SceneNode
{
public:
	PlayerShipNode() : SceneNode()
	{
		shape_ray_int_1.setFillColor(sf::Color::Black);
		shape_ray_int_1.setRadius(8);
		shape_ray_int_1.setOrigin(4, 4);
		shape_ray_int_1.setOutlineColor(sf::Color::White);
		shape_ray_int_1.setOutlineThickness(1);

		shape_ray_int_2.setFillColor(sf::Color::White);
		shape_ray_int_2.setRadius(8);
		shape_ray_int_2.setOrigin(4, 4);
		shape_ray_int_2.setOutlineColor(sf::Color::Black);
		shape_ray_int_2.setOutlineThickness(1);
	}

	~PlayerShipNode() {}

	void update() override;
	void start() override;
	void render() override;

private:
	void onCollide(BaseEvent* e);

	Raycast cast;
	sf::CircleShape shape_ray_int_1;
	sf::CircleShape shape_ray_int_2;

	sf::Vector2f rotateToMouse();
	sf::Vector2f handleMovement();

	void shoot(sf::Vector2f direction);

	CollisionNode* _collision;
	ControlScheme* _controlScheme;
	TransformNode* _transform;
};

