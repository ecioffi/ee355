#include <iostream>
#include <string>
#include <random>
#include <functional>
#include <list>
#include <chrono>
#include <thread>

#include "mastermap.h"
#include "gfx.h"
#include "books.h"

void Hunter::divorce()
{
	def /= 1.5;
	partner->champion = false;
	champion = false;
}

Point Entity::graveyard = Point(100, 100);

std::uniform_int_distribution<int> deciDist(1,10);
auto deciRand = bind(deciDist, gen);

MasterMap mm;

void wait(int d = 200)
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
}

int main(int argc, char const *argv[])
{
	mm.initEntities();

	draw();
	int itt = 0;
	while (mm.monsters.size() > 0 && !mm.hunters.empty())
	{
		std::cout << "ITERATION " << itt << ":" << std::endl;
		mm.print();

		for (auto& e : mm.entities)
			e.get().interact(mm.entities);
		mm.emptyGraveyard();
		for (auto& e : mm.entities)
			e.get().move();
		draw();
		wait();

		itt++;
	}

	std::cout << std::endl;
	if (mm.hunters.empty())
		std::cout << "All hunters DEAD. Monsters roam the earth." << std::endl;
	else
		std::cout << "All monster defeated -- Hunters win!" << std::endl;
}