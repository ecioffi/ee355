#pragma once

#include <string>
#include <random>

std::random_device rnd;
std::mt19937 gen(rnd());

enum Gender {
	Male,
	Female,
	NonBinary,
	Fluid,
	GenderIsSocialConstruct
};

struct Color {
 	unsigned char r, g, b;
 	constexpr Color(unsigned char R, unsigned char G, unsigned char B) : r(R), g(G), b(B) { }
 	Color() { }
};

namespace Colors {
	constexpr Color White = Color(255, 255, 255);
	constexpr Color Black = Color(0, 0, 0);
	constexpr Color Red = Color(255, 0, 0);
	constexpr Color Green = Color(0, 255, 0);
	constexpr Color Blue = Color(0, 0, 255);
};

enum Shape {
	Square,
	Triangle,
	Circle
};

struct Pair {
	constexpr Pair(int X, int Y) : x(X), y(Y) { }
	int x, y;
};

enum Cardinal {
	North,
	NorthEast,
	East,
	SouthEast,
	South,
	SouthWest,
	West,
	NorthWest
};

static constexpr Pair deltas[] = { Pair(0, 1), Pair(1, 1), Pair(1, 0), Pair(1, -1), Pair(0, -1), Pair(-1, -1), Pair(-1, 0), Pair(-1, 1) };
static constexpr Pair delta(Cardinal c) { return deltas[c]; }

class Point {
public:
	Point(int X, int Y) : x(X), y(Y) { }
	Point() { x=0; y=0; }

	int x, y;

	void set(int x_, int y_)
	{
		x = x_;
		y = y_;
	}

	Point& operator+=(const Cardinal& rhs)
	{
		//std::cout << "test" << std::endl;
		x += delta(rhs).x;
		y += delta(rhs).y;
		return *this;
    }

    friend Point operator+(Point lhs, const Cardinal& rhs)
	{
		lhs.x += delta(rhs).x;
		lhs.y += delta(rhs).y;
		return lhs;
	}
};

// Point operator+(const Point& lhs, const Cardinal& rhs)
// {
// 	Point r = Point(lhs.x + delta(rhs).x, lhs.y + delta(rhs).y);
// 	return r;
// }

bool operator<(const Point& lhs, const Point& rhs)
{
	return lhs.x < rhs.x || (!(rhs.x < lhs.x) && lhs.y < rhs.y);
}

static inline std::string pairText(const Point& p)
{
	return "(" + std::to_string(p.x) + ", " + std::to_string(p.y) + ")";
}