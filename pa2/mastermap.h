#pragma once

#include <map>
#include <typeinfo>

#include "types.h"
#include "books.h"

std::uniform_int_distribution<int> gridDist(0,15);
auto randXY = bind(gridDist, gen);

class MasterMap {
public:
	HunterBook hunterB;
	PalicoBook palicoB;
	MonsterBook monsterB;

	std::list<Hunter>& hunters = hunterB.list;
	std::list<Palico>& palicos = palicoB.list;
	std::list<Monster>& monsters = monsterB.list;

	std::multimap<std::reference_wrapper<Point>, std::reference_wrapper<Entity>> entities;

	MasterMap()
	{
		
	}

	Point randOpenPoint()
	{
		while (true)
		{
			Point p = Point(randXY(), randXY());
			if (entities.count(p) == 0)
				return p;
		}
	}

	void newHunter(Point p)
	{
		hunters.emplace_back(p);
		entities.insert(make_pair(hunters.back().pos(), std::ref(hunters.back())));
	}

	void newPalico(Point p)
	{
		palicos.emplace_back(p);
		entities.insert(make_pair(palicos.back().pos(), std::ref(palicos.back())));
	}

	void newMonster(Point p)
	{
		monsters.emplace_back(p);
		entities.insert(make_pair(monsters.back().pos(), std::ref(monsters.back())));
	}

	void emptyGraveyard()
	{
		entities.erase(Entity::graveyard);
		hunters.remove_if([](Hunter h) { return h.coordinate == Entity::graveyard; });
		palicos.remove_if([](Palico p) { return p.coordinate == Entity::graveyard; });
		monsters.remove_if([](Monster m) { return m.coordinate == Entity::graveyard; });
	}

	void remove(Entity& e)
	{
		e.sendToGraveyard();
		emptyGraveyard();
	}

	void print()
	{
		for (auto& p : entities)
		{
			std::cout << typeid(p.second.get()).name() << " at ";
			std::cout << p.second.get().coordinate.str() << std::endl;
		}
		std::cout << std::endl;
	}
};