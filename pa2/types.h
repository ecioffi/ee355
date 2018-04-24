#pragma once

#include <random>
#include <vector>
#include <functional>

static std::random_device rnd;
static std::mt19937 gen(rnd());

static std::uniform_int_distribution<int> cardDist(0, 7);
static auto randCard = bind(cardDist, gen);
static std::uniform_int_distribution<int> genderDist(0, 3);
static auto randGender = bind(genderDist, gen);

static std::vector<std::string> Genders = {
	"Male",
	"Female",
	"NonBinary",
	"Fluid"
};

static std::string randomGender() { return Genders[randGender()]; }

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

	static  std::vector<Color> colorBank = {Red, Green, Blue, Orange, Purple, Cyan, Magenta, Lime, Pink, Teal, Lavender, Brown, Maroon, Mint, Olive, Coral, Navy, Grey};
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

static Cardinal randCardinal()
{
	return static_cast<Cardinal>(randCard());
}