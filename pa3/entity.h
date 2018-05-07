#pragma once

#include <string>
#include <thread>

#include "point.h"
#include "stuff.h"
#include "names.h"
#include "gfx.h"

static std::uniform_int_distribution<int> boolDist(0,1);
static auto randBool = bind(boolDist, gen);

static std::uniform_int_distribution<int> ageDist(7,78);
static auto randAge = bind(ageDist, gen);

class Entity {
	public:
		std::string name;
		std::string fName, lName;
		int maxHP, hp, atk, def;
		Color color;
		std::string gender = randomGender();
		Point coordinate;
		int age = randAge();
		static Point graveyard;
		virtual std::string typeName() = 0;

		Entity(int HP, int attack, int defense, Point point) : maxHP(HP), atk(attack), def(defense), coordinate(point)
		{
			fName = randomName();
			lName = randomName();
			name = fName + " " + lName;
			hp = maxHP;
			color = Colors::colorBank.back();
			Colors::colorBank.back();
			Colors::colorBank.pop_back();
		}

		virtual void interact(std::list<std::reference_wrapper<Entity>>& entities) = 0;
		virtual void draw() = 0;

		std::thread interactThread(std::list<std::reference_wrapper<Entity>>& entities)
		{
			return std::thread([=] { interact(entities); });
      	}

		void sendToGraveyard()
		{
			coordinate = graveyard;
		}

		bool inYard()
		{
			return coordinate == graveyard;
		}

		void checkKilled()
		{
			if (dead())
			{
				std::cout << typeName() << name << " has been defeated!" << std::endl;
				lastRites();
				sendToGraveyard();
			}
		}

		void attack(Entity& enemy)
		{
			std::cout << typeName() << name << " attacks " << enemy.typeName() << enemy.name << "! " <<
						 "Her HP drops from " << enemy.hp << " to ";
			enemy.hp = std::max(enemy.hp - std::max(0, atk - enemy.def), 0);
			std::cout << enemy.hp << "." << std::endl;
			enemy.checkKilled();
		}

		void battle(Entity& enemy)
		{
			if (randBool())
			{
				while (alive())
				{
					attack(enemy);
					if (enemy.alive())
						enemy.attack(*this);
					else
						return;
				}
			}
			else
			{
				while (enemy.alive())
				{
					enemy.attack(*this);
					if (alive())
						attack(enemy);
					else
						return;
				}
			}
		}

		virtual void move()
		{
			Cardinal c = randCardinal();
			while ((coordinate + c).outOfBounds())
				c = randCardinal();

			coordinate += c;
		}

		virtual void lastRites() { }
		virtual void divorce() { }
		bool alive() { return (hp > 0); }
		bool dead() { return !alive(); }
		std::reference_wrapper<Point> pos() { return std::ref(coordinate); }
};