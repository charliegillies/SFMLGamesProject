#pragma once
class Rectangle
{
public:
	Rectangle() {}
	Rectangle(int x, int y, int width, int height)
		: width(width), height(height), x(x), y(y) {}

	~Rectangle() {}

	int width;
	int height;
	int x;
	int y;

	bool containsPoint(int tx, int ty)
	{
		return (tx >= x && tx <= (x + width))
			&& (ty >= y && ty <= (y + height));
	}
};