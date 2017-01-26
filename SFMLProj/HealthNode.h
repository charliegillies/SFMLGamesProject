#pragma once
#include "SceneNode.h"

/*
	Simple data driven class that holds the maximum and current amount of HP
	of the scene node. Also has some basic util methods for querying.
*/
class HealthNode : public SceneNode
{
public:
	HealthNode(const int maxHP) : maxHP(maxHP), HP(maxHP) { }
	~HealthNode() { }

	// The maximum hp of the scene node
	const int maxHP;

	// The current hp of the scene node
	int HP;

	// Reduces HP, limits hp to 0.
	void damage(int dmg)
	{
		HP -= dmg;

		if (HP < 0)
			HP = 0;
	}

	// Increases HP, limits hp to 0.
	void heal(int amount)
	{
		HP += amount;

		if (HP > maxHP)
			HP = maxHP;
	}

	// Checks if HP is 0 or below.
	bool isDead()
	{
		return HP <= 0;
	}

	// Checks if the HP is max or above.
	bool atFullHP()
	{
		return HP >= maxHP;
	}

	// Gets the percentage which is calculated by
	// (HP / max HP) * 100
	float getPercentageHP()
	{
		// conv values to float for division
		float f_hp = HP;
		float m_hp = maxHP;

		return (f_hp / m_hp) * 100.0f;
	}

	string getNodeTag() override
	{
		return NodeTag::health_node;
	}

};