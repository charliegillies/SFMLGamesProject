#include "CollisionMap.h"
#include <math.h>
#include <iostream>

vector<CollisionNode*>& CollisionMap::getCollidersInCell(int x, int y)
{
	return _grid[y][x];
}

void CollisionMap::buildMap()
{
	clearGrid();

	for (auto i = _colliders->begin(); i != _colliders->end(); ++i)
	{
		// get the iterator value
		CollisionNode* entity = (*i);

		int min_x = entity->getTopX() / cellSize;
		int min_y = entity->getTopY() / cellSize;

		int max_x = (entity->getTopX() + entity->getWidth()) / cellSize;
		int max_y = (entity->getTopY() + entity->getHeight()) / cellSize;

		// the entity has gone out of collision bounds
		if (min_x < 0 || min_y < 0 || min_x >= width || min_y >= height || max_x >= width || max_y >= height)
		{
			std::cout << "Entity has gone out of bounds. This must be handled!!" << endl;
			return;
		}



		for (int x = min_x; x <= max_x; x++)
		{
			for (int y = min_y; y <= max_y; y++)
			{
				vector<CollisionNode*>& cell = _grid[y][x];
				cell.push_back(entity);
			}
		}
	}
}

void CollisionMap::clearGrid()
{
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			getCollidersInCell(x, y).clear();
}