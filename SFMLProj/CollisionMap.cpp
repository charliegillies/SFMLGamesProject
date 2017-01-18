#include "CollisionMap.h"
#include <math.h>
#include <iostream>

void CollisionMap::buildMap()
{
	for (auto i = _colliders.begin(); i != _colliders.end(); ++i)
	{
		// get the iterator value
		CollisionNode* entity = (*i);

		int min_x = entity->getX() / cellSize;
		int min_y = entity->getY() / cellSize;

		// the entity has gone out of collision bounds
		if (min_x < 0 || min_y < 0)
		{
			std::cout << "Entity has gone out of bounds. This must be handled!!" << endl;
			return;
		}

		int max_x = (entity->getX() + entity->getWidth()) / cellSize;
		int max_y = (entity->getY() + entity->getHeight()) / cellSize;

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