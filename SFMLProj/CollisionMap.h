#pragma once
#include <vector>
#include "CollisionNode.h"

/*
	The collision map is responsible for doing our spatial partitioning
	where nodes colliders are split into 
*/
class CollisionMap
{
public:
	static const int width = 40;
	static const int height = 40;
	static const int cellSize = 50;
	
	CollisionMap(std::vector<CollisionNode*>& colliders) 
		: _colliders(colliders) {}
	
	~CollisionMap() {}

	// builds a map of colliding nodes 
	void buildMap();

private:
	std::vector<CollisionNode*> _grid[height][width];

	std::vector<CollisionNode*>& _colliders;
};