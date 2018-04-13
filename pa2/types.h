#pragma once

#include <string>

struct constPair {
	constexpr constPair(int X, int Y) : x(X), y(Y) { }
	int x, y;
};

enum Cardinal {
	North,
	South,
	East,
	West
};

static constexpr constPair deltas[] = { constPair(0, 1), constPair(0, -1), constPair(1, 0), constPair(-1, 0) };
static inline constexpr constPair delta(Cardinal c) { return deltas[c]; }

struct orderedPair {
	orderedPair(int X, int Y) : x(X), y(Y) { }

	int x, y;

	orderedPair& operator+=(const Cardinal& rhs)
	{
		//std::cout << "test" << std::endl;
		x += delta(rhs).x;
		y += delta(rhs).y;
		return *this;
    }

    friend orderedPair operator+(orderedPair lhs, const Cardinal& rhs)
	{
		lhs.x += delta(rhs).x;
		lhs.y += delta(rhs).y;
		return lhs;
	}
};

// orderedPair operator+(const orderedPair& lhs, const Cardinal& rhs)
// {
// 	orderedPair r = orderedPair(lhs.x + delta(rhs).x, lhs.y + delta(rhs).y);
// 	return r;
// }

bool operator<(const orderedPair& lhs, const orderedPair& rhs)
{
	return lhs.x < rhs.x || (!(rhs.x < lhs.x) && lhs.y < rhs.y);
}

static inline std::string pairText(const orderedPair& p)
{
	return "(" + std::to_string(p.x) + ", " + std::to_string(p.y) + ")";
}