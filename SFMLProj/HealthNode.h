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

	void damage(int dmg)
	{
		HP -= dmg;

		if (HP < 0)
			HP = 0;
	}

	void heal(int amount)
	{
		HP += amount;

		if (HP > maxHP)
			HP = maxHP;
	}

	bool isDead()
	{
		return HP <= 0;
	}

	bool atFullHP()
	{
		return HP >= maxHP;
	}

	float getPercentageHP()
	{
		return (HP / maxHP) * 100;
	}

private:
	// The maximum hp of the scene node
	const int maxHP;

	// The current hp of the scene node
	int HP;
};