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
	static const int width = 20;
	static const int height = 20;
	static const int cellSize = 100;

	std::vector<CollisionNode*>& getCollidersInCell(int x, int y);
	
	CollisionMap(std::vector<CollisionNode*>* colliders) 
		: _colliders(colliders) {}
	
	~CollisionMap() {}

	// builds a map of colliding nodes 
	void buildMap();

	void clearGrid();

private:
	std::vector<CollisionNode*> _grid[height][width];

	std::vector<CollisionNode*>* _colliders;
};