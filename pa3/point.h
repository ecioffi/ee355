#pragma once

#include <string>

#include "types.h"

class Point {
public:
	Point(short X, short Y) : x(X), y(Y) { }
	constexpr Point(const int X, const int Y) : x(X), y(Y) { }
	Point() { x=0; y=0; }

	int x, y;

	void set(int x_, int y_)
	{
		x = x_;
		y = y_;
	}

	std::string str()
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	}

	bool outOfBounds()
	{
		return (x < 0) || (x > 15) || (y < 0) || (y > 15);
	}

	Point& operator+=(const Cardinal& rhs);
};


bool operator<(const Point& lhs, const Point& rhs);
bool operator==(const Point& lhs, const Point& rhs);
bool operator!=(const Point& lhs, const Point& rhs);
std::string PointText(const Point& p);
Point operator+(const Point& lhs, const Cardinal& rhs);