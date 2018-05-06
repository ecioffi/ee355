#include "point.h"
#include "types.h"

static constexpr Point deltas[] = { Point(0, 1), Point(1, 1), Point(1, 0), Point(1, -1), Point(0, -1), Point(-1, -1), Point(-1, 0), Point(-1, 1) };
static constexpr Point delta(Cardinal c) { return deltas[c]; }

bool operator<(const Point& lhs, const Point& rhs)
{
	return lhs.x < rhs.x || (!(lhs.x < rhs.x) && (lhs.y < rhs.y));
}

bool operator==(const Point& lhs, const Point& rhs)
{
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool operator!=(const Point& lhs, const Point& rhs)
{
	return (lhs.x != rhs.x) || (lhs.y != rhs.y);
}

Point operator+(const Point& lhs, const Cardinal& rhs)
{
	Point r = Point(lhs.x + delta(rhs).x, lhs.y + delta(rhs).y);
	return r;
}

std::string PointText(const Point& p)
{
	return "(" + std::to_string(p.x) + ", " + std::to_string(p.y) + ")";
}

Point& Point::operator+=(const Cardinal& rhs)
{
	//std::cout << "test" << std::endl;
	x += delta(rhs).x;
	y += delta(rhs).y;
	return *this;
}