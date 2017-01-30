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
	static const int width = 8;
	static const int height = 6;
	static const int cellSize = 200;

	static const int world_top_left_x = 0;
	static const int world_top_left_y = 0;
	static const int world_bot_right_x = (width * cellSize);
	static const int world_bot_right_y = (height * cellSize);

	vector<CollisionNode*>& getCollidersInCell(int x, int y);
	
	CollisionMap(std::vector<CollisionNode*>* colliders) 
		: _colliders(colliders), _drawGrid()
	{
		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				sf::RectangleShape& shape = _drawGrid[y][x];
				shape.setPosition(x * cellSize, y * cellSize);
				shape.setSize(sf::Vector2f(cellSize, cellSize));
				shape.setFillColor(sf::Color(255, 255, 255, 128));
				shape.setOutlineColor(sf::Color::Black);
				shape.setOutlineThickness(1);
			}
		}
	}
	
	~CollisionMap() {}

	// builds a map of colliding nodes 
	void buildMap();

	void clearGrid();

	// draws the test grid for debug purposes
	void drawDebugGrid(Game* game);

private:
	std::vector<CollisionNode*> _grid[height][width];
	sf::RectangleShape _drawGrid[height][width];

	std::vector<CollisionNode*>* _colliders;
};