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
	CollisionMap(int width, int height, int cellSize, std::vector<CollisionNode*>& colliders) 
		: width(width), height(height), cellsize(cellsize), _colliders(colliders) {}
	
	~CollisionMap() {}

	// builds a map of colliding nodes 
	void buildMap();

private:
	int width;
	int height;
	int cellsize;

	std::vector<CollisionNode*>& _colliders;
};