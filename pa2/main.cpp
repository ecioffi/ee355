#include <iostream>
#include <string>
#include <random>
#include <functional>
#include <chrono>
#include <map>
#include <list>
#include <thread>

#include "mastermap.h"
#include "gfx.h"
#include "books.h"

using namespace std;

void Hunter::divorce()
{
	def /= 1.5;
	partner->champion = false;
	champion = false;
}

Point Entity::graveyard = Point(100, 100);

uniform_int_distribution<int> deciDist(1,10);
auto deciRand = bind(deciDist, gen);

MasterMap mm;

bool inBounds(int value, int low, int high)
{
	return (low <= value) && (value <= high);
}

void pause(std::string message)
{
	chrono::duration<double> elapsed(0);

	cout << message << endl;
	while (chrono::duration_cast<chrono::milliseconds>(elapsed).count() < 100)
	{
		auto start = chrono::high_resolution_clock::now();
		cin.ignore();
		auto end = chrono::high_resolution_clock::now();
		elapsed += end-start;
	}
}

void pause() { pause(""); }

void wait(int d = 800)
{
	std::chrono::milliseconds dur(d);
	std::this_thread::sleep_for(dur);
}

void draw()
{
	GFX::clear();
	GFX::drawGrid();

	for (auto& p : mm.entities)
		if (p.get().pos() != Entity::graveyard)
			p.get().draw();

		GFX::show();
		wait(100);
}

int main(int argc, char const *argv[])
{
	//\MonsterBook mb;
	mm.initEntities();

	draw();
	while (mm.monsters.size() > 0 && (mm.hunters.size() + mm.palicos.size()) > 0)
	{
		for (auto& e : mm.entities)
			e.get().interact(mm.entities);
		mm.emptyGraveyard();
		for (auto& e : mm.entities)
			e.get().move();
		//draw();
	}
}