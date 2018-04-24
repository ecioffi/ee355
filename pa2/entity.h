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
		std::string typeName;

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

		virtual bool isEnemy(Entity& e) = 0;
		virtual void interact(std::list<std::reference_wrapper<Entity>>& entities) = 0;
		virtual void draw() const = 0;

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
			if (hp == 0)
			{
				std::cout << typeName << " " << name_ << " has been defeated!" << std::endl;
				sendToGraveyard();
				lastRites();
			}
		}

		void attack(Entity& enemy)
		{
			std::cout << typeName << " " << name_ << " attacks " << enemy.name_ << "! " <<
						 enemy.typeName << " " << enemy.name_ << "'s HP drops from " << enemy.hp << " to ";
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

		/*void defend(Entity& enemy)
		{
			defending = false;
			std::cout << typeName << " " << name_ << " defends against " << enemy.name_ << "! ";
			std::cout << name_ << "'s HP drops from " << hp << " to ";
			hp = std::max(hp - std::max(enemy.atk - (def * 2), 0), 0);
			std::cout << hp << "." << std::endl;
			checkKilled();
		}*/

		virtual void lastRites() { }
		std::string name() { return name_; }
		bool alive() { return (hp > 0); }
		std::reference_wrapper<Point> pos() { return coordinate; }
};