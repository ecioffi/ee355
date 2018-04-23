#pragma once

#include <string>
#include <random>
#include <vector>

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

//colors from https://sashat.me/2017/01/11/list-of-20-simple-distinct-colors/
namespace Colors {
	constexpr Color White = Color(255, 255, 255);
	constexpr Color Black = Color(0, 0, 0);
	constexpr Color Red = Color(230, 25, 75);
	constexpr Color Green = Color(60, 180, 75);
	constexpr Color Blue = Color(0, 130, 200);
	constexpr Color Yellow = Color(255, 255, 25);
	constexpr Color Orange = Color(245, 130, 48);
	constexpr Color Purple = Color(145, 30, 180);
	constexpr Color Cyan = Color(70, 240, 240);
	constexpr Color Magenta = Color(240, 50, 230);
	constexpr Color Lime = Color(210, 190, 190);
	constexpr Color Pink = Color(250, 190, 190);
	constexpr Color Teal = Color(0, 128, 128);
	constexpr Color Lavender = Color(230, 190, 255);
	constexpr Color Brown = Color(170, 110, 40);
	constexpr Color Beige = Color(255, 250, 200);
	constexpr Color Maroon = Color(128, 0, 0);
	constexpr Color Mint = Color(170, 255, 195);
	constexpr Color Olive = Color(128, 128, 0);
	constexpr Color Coral = Color(255, 215, 180);
	constexpr Color Navy = Color(0, 0, 128);
	constexpr Color Grey = Color(128, 128, 128);

	std::vector<Color> colorBank = {Red, Green, Blue, Orange, Purple, Cyan, Magenta, Lime, Pink, Teal, Lavender, Brown, Maroon, Mint, Olive, Coral, Navy, Grey};
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
	constexpr Point(const int X, const int Y, bool k) : x(X), y(Y) { }
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

namespace std {

	template<> struct hash<std::reference_wrapper<Point>>
	{
		std::size_t operator()(const Point& p) const noexcept
		{
			return p.x << 15 + p.y;
		}
	};
}

// Point operator+(const Point& lhs, const Cardinal& rhs)
// {
// 	Point r = Point(lhs.x + delta(rhs).x, lhs.y + delta(rhs).y);
// 	return r;
// }

bool operator==(const Point& lhs, const Point& rhs)
{
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

static inline std::string pairText(const Point& p)
{
	return "(" + std::to_string(p.x) + ", " + std::to_string(p.y) + ")";
}