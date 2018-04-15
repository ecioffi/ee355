#include <iostream>
#include <string>
#include <random>
#include <functional>
#include <chrono>
#include <map>
#include <list>
#include <typeinfo>

#include "hunter.h"
#include "monster.h"
#include "palico.h"
#include "gfx.h"

using namespace std;

list<Hunter> hunters;
list<Palico> palicos;
list<Monster> monsters;
multimap<reference_wrapper<Point>, reference_wrapper<Entity>> entities;

uniform_int_distribution<int> deciDist(1,10);
uniform_int_distribution<int> gridDist(0,15);
auto deciRand = bind(deciDist, gen);
auto randXY = bind(gridDist, gen);

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

Point randOpenPoint()
{
	while (true)
	{
		Point p = Point(randXY(), randXY());
		if (entities.count(p) == 0)
			return p;
	}
}

void initEntities()
{
	for (int i = 0; i < 3; i ++)
	{
		hunters.emplace_back(randOpenPoint());
		entities.insert(make_pair(hunters.back().pos(), ref(hunters.back())));
	}
	for (int i = 0; i < 5; i ++)
	{
		palicos.emplace_back(randOpenPoint());
		entities.insert(make_pair(palicos.back().pos(), ref(palicos.back())));
	}
	for (int i = 0; i < 10; i ++)
	{
		monsters.emplace_back(randOpenPoint());
		entities.insert(make_pair(monsters.back().pos(), ref(monsters.back())));
	}
}

int main(int argc, char const *argv[])
{
	//initEntities();
	GFX::drawGrid();
	hunters.emplace_back(Point(0, 0));
	entities.insert(make_pair(hunters.back().pos(), ref(hunters.back())));
	hunters.back().coordinate.x=5;
	Point p = Point(0, 0);
	cout << entities.count(p) << endl;
	p = Point(5, 0);
	cout << entities.count(p) << endl;
	for (auto& p : entities)
	{
		p.second.get().draw();
		cout << typeid(p.second.get()).name() << endl;
	}
	GFX::show();
}