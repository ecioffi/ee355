#pragma once

#include <iostream>
#include <string>
#include <random>
#include <functional>
#include <chrono>

#include "hunter.h"
#include "monster.h"
#include "palico.h"
#include "gfx.h"

class Game {
public:
	static Game& getInstance()
	{
		static Game instance;
		return instance;
	}
private:
	Game(const Game&) = delete;
	void operator=(const Game&) = delete;

	GFX gfx;

	std::multimap<Point, Entity> entities;

	std::uniform_int_distribution<int> deciDist(1,10);
	std::uniform_int_distribution<int> gridDist(0,15);
	static auto deciRand = bind(deciDist, gen);
	static auto randXY = bind(deciDist, gen);

	bool inBounds(int value, int low, int high)
	{
		return (low <= value) && (value <= high);
	}

	void pause(std::string message)
	{
		chrono::duration<double> elapsed(0);

		std::cout << message << std::endl;
		while (chrono::duration_cast<chrono::milliseconds>(elapsed).count() < 100)
		{
			auto start = chrono::high_resolution_clock::now();
			std::cin.ignore();
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
			entities.insert(std::make_pair(randOpenPoint(), Hunter()));
		for (int i = 0; i < 5; i ++)
			entities.insert(std::make_pair(randOpenPoint(), Palico()));
		for (int i = 0; i < 10; i ++)
			entities.insert(std::make_pair(randOpenPoint(), Monster()));
	}

	Game()
	{
		initEntities();
		gfx.drawScreen();
	}
};