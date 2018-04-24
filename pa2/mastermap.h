#pragma once

#include <typeinfo>

#include "types.h"
#include "entities.h"

std::uniform_int_distribution<int> gridDist(0,15);
auto randXY = bind(gridDist, gen);

class MasterMap {
public:
	std::list<Hunter> hunters;
	std::list<Palico> palicos;
	std::list<Monster> monsters;

	std::list<std::reference_wrapper<Entity>> entities;

	MasterMap()
	{
		
	}

	Point randOpenPoint()
	{
		while (true)
		{
			Point p = Point(randXY(), randXY());
			for (auto e : entities)
				if (e.get().pos() == p)
					continue;
			return p;
		}
	}

	void newHunter(Point p)
	{
		hunters.emplace_back(p);
		entities.push_back(hunters.back());
	}

	void newPalico(Point p)
	{
		palicos.emplace_back(p);
		entities.push_back(palicos.back());
	}

	void newMonster(Point p)
	{
		monsters.emplace_back(p);
		entities.push_back(monsters.back());
	}

	void initEntities()
	{
		for (int i = 0; i < 3; i ++)
			newHunter(randOpenPoint());

		for (int i = 0; i < 5; i ++)
			newPalico(randOpenPoint());

		for (int i = 0; i < 10; i ++)
			newMonster(randOpenPoint());
	}

	void emptyGraveyard()
	{
		entities.remove_if([](Entity& e) { return e.coordinate == Entity::graveyard; });
		hunters.remove_if([](Hunter& h) { return h.coordinate == Entity::graveyard; });
		palicos.remove_if([](Palico& p) { return p.coordinate == Entity::graveyard; });
		monsters.remove_if([](Monster& m) { return m.coordinate == Entity::graveyard; });
	}

	void print()
	{
		for (auto& p : entities)
		{
			std::cout << typeid(p.get()).name() << " at ";
			std::cout << p.get().coordinate.str() << " ";
			std::cout << "inYard: " << (p.get().pos() == Entity::graveyard) << std::endl;
		}
		std::cout << std::endl;
	}
};