#pragma once

#include <string>

#include "types.h"
#include "stuff.h"
#include "names.h"
#include "gfx.h"

std::uniform_int_distribution<int> boolDist(0,1);
auto randBool = bind(boolDist, gen);

class Entity {
	protected:
		std::string name_;
		std::string fName, lName;
		int age, maxHP, hp, atk, def;
		Color color;
		Gender gender;

		//Equipment eqip;
		//Sword sword;
		
	public:
		Point coordinate;
		static Point graveyard;
		virtual std::string typeName() = 0;
		Color getColor() { return color; }

		Entity(int HP, int attack, int defense, Point point) : maxHP(HP), atk(attack), def(defense), coordinate(point)
		{
			fName = randomName();
			lName = randomName();
			name_ = fName + " " + lName;
			hp = maxHP;
			color = Colors::colorBank.back();
			Colors::colorBank.back();
			Colors::colorBank.pop_back();
		}

		virtual void interact(std::list<std::reference_wrapper<Entity>>& entities) = 0;
		virtual void draw() = 0;

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
				std::cout << typeName() << name_ << " has been defeated!" << std::endl;
				lastRites();
				sendToGraveyard();
			}
		}

		void attack(Entity& enemy)
		{
			std::cout << typeName() << name_ << " attacks " << enemy.typeName() << enemy.name_ << "! " <<
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
		virtual void divorce() { } //KLUDGE MUST FIX!!!!!! everything is a kludge lololll
		std::string name() { return name_; }
		bool alive() { return (hp > 0); }
		bool dead() { return !alive(); }
		std::reference_wrapper<Point> pos() { return std::ref(coordinate); }
};