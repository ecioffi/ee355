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

void wait(int d = 800)
{
	std::chrono::milliseconds dur(d);
	std::this_thread::sleep_for(dur);
}

void initEntities()
{
	for (int i = 0; i < 3; i ++)
		mm.newHunter(mm.randOpenPoint());

	for (int i = 0; i < 5; i ++)
		mm.newPalico(mm.randOpenPoint());

	for (int i = 0; i < 10; i ++)
		mm.newMonster(mm.randOpenPoint());
}

void draw()
{
	GFX::clear();
	GFX::drawGrid();

	for (auto& p : mm.entities)
		if (p.first != Entity::graveyard)
			p.second.get().draw();

		GFX::show();
		//wait(100);
}

int main(int argc, char const *argv[])
{
	initEntities();
	//for (int i = 0; i < 3; i ++)
	//mm.newHunter(Point(0, 0));
	//mm.newPalico(Point(0, 0));
	//mm.newPalico(Point(0, 0));
	// for (int i = 0; i < 3; i ++)
	// 	mm.newHunter(Point(0, 5));
	while (false)
	{
		draw();
		mm.hunters.back().move();
	}

	while (mm.monsters.size() > 0 && (mm.hunters.size() + mm.palicos.size()) > 0)
	{
		//break;
		draw();

		std::list<std::list<reference_wrapper<Entity>>> squares;
		for (auto it = mm.entities.begin(), next = mm.entities.begin(); it != mm.entities.end(); it = next)
		{
			while (next != mm.entities.end() && next->first == it->first)
				++next;
			//std::cout << "new sq: " << it->first.get().str() << endl;

			list<reference_wrapper<Entity>> sq;
			for (; it != next; ++it)
				sq.push_back(it->second);

			squares.push_back(sq);
		}

		std::cout << "done" << endl;

		for (auto& sq : squares)
		{
			if (sq.size() == 1)
				continue;
			for (auto& e : sq)
			{
				//std::cout << typeid(e.get()).name() << endl;
				e.get().interact(sq);
			}
		}

		for (auto& sq : squares)
		{
			for (auto& e : sq)
			{
				if (!e.get().inYard())
				{
					e.get().move();
				}
			}
		}

		mm.print();
		mm.emptyGraveyard();
		mm.print();
	}
}