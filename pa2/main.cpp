#include <iostream>
#include <string>
#include <random>
#include <functional>
#include <chrono>
#include <map>
#include <list>

#include "mastermap.h"
#include "gfx.h"

using namespace std;

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

void initEntities()
{
	for (int i = 0; i < 3; i ++)
		mm.newHunter(mm.randOpenPoint());

	for (int i = 0; i < 5; i ++)
		mm.newPalico(mm.randOpenPoint());

	for (int i = 0; i < 10; i ++)
		mm.newMonster(mm.randOpenPoint());
}

int main(int argc, char const *argv[])
{
	//initEntities();
	for (int i = 0; i < 3; i ++)
		mm.newHunter(Point(0, 0));
	for (int i = 0; i < 3; i ++)
		mm.newHunter(Point(0, 5));
	GFX::clear();
	GFX::drawGrid();

	std::list<std::list<reference_wrapper<Entity>>> squares;
	for (auto it = mm.entities.begin(), next = mm.entities.begin(); it != mm.entities.end(); it = next)
	{
		while (next != mm.entities.end() && next->first == it->first)
			++next;
		std::cout << "new sq: " << it->first.get().str() << endl;

		if (mm.entities.count(it->first) > 1)
		{
			list<reference_wrapper<Entity>> sq;
			for (; it != next; ++it)
			{
				sq.push_back(it->second);
			}

			squares.push_back(sq);
		}
	}

	for (auto& sq : squares)
	{
		for (auto& e : sq)
		{
			e.get().interact(sq);
		}
	}

	for (auto& p : mm.entities)
	{
		if (p.first != Entity::graveyard)
			p.second.get().draw();
	}

	GFX::show();
}