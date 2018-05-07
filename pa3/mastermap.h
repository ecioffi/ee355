#pragma once

#include <typeinfo>
#include <algorithm>

#include "types.h"
#include "entities.h"
#include "books.h"

std::uniform_int_distribution<int> gridDist(0,15);
auto randXY = bind(gridDist, gen);

class MasterMap {
private:
	HunterBook hb;
	PalicoBook pb;
	MonsterBook mb;
public:
	std::forward_list<Hunter>& hunters = hb.data();
	std::vector<Palico>& palicos = pb.data();
	std::list<Monster>& monsters = mb.data();

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
		hunters.emplace_front(p);
		entities.push_back(hunters.front());
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
		//palicos.erase(std::remove_if(palicos.begin(), palicos.end(), [](Palico& p) { return p.coordinate == Entity::graveyard; }));
		monsters.remove_if([](Monster& m) { return m.coordinate == Entity::graveyard; });
	}

	void print()
	{
		std::cout << entities.size() << std::endl;
		for (auto& p : entities)
		{
			std::cout << typeid(p.get()).name() << " at ";
			std::cout << p.get().coordinate.str() << " ";
			std::cout << "dead: " << (p.get().pos() == Entity::graveyard) << std::endl;
		}
		std::cout << std::endl;
	}
};