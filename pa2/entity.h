#pragma once

#include <string>

#include "types.h"
#include "stuff.h"
#include "names.h"
#include "gfx.h"

class Entity {
	protected:
		std::string name_;
		std::string fName, lName;
		int age, maxHP, hp, atk, def;
		Color color;
		Gender gender;

		//Equipment eqip;
		//Sword sword;

		
		bool defending = false;
	public:
		Point coordinate;
		static Point graveyard;

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

		virtual void draw() const = 0;

		void sendToGraveyard()
		{
			coordinate = graveyard;
		}

		void checkKilled()
		{
			if (hp == 0)
			{
				std::cout << name_ << " has been defeated!" << std::endl;
				lastRites();
			}
		}

		void attack(Entity& enemy)
		{
			defending = false;
			if (enemy.defending)
			{
				enemy.defend(*this);
				return;
			}
			std::cout << name_ << " attacks " << enemy.name_ << "! " <<
						 enemy.name_ << "'s HP drops from " << enemy.hp << " to ";
			enemy.hp = std::max(enemy.hp - std::max(0, atk - enemy.def), 0);
			std::cout << enemy.hp << "." << std::endl;
			enemy.checkKilled();
		}

		void defend(Entity& enemy)
		{
			defending = false;
			std::cout << name_ << " defends against " << enemy.name_ << "! ";
			std::cout << name_ << "'s HP drops from " << hp << " to ";
			hp = std::max(hp - std::max(enemy.atk - (def * 2), 0), 0);
			std::cout << hp << "." << std::endl;
			checkKilled();
		}

		void heal(int ammount)
		{
			if (hp == maxHP)
			{
				std::cout << name_ << " is already fully healed at " << hp << " HP." << std::endl;
				return;
			}
			std::cout << name_ << "'s HP increaces from " << hp << " to " << std::min(maxHP, hp + ammount) << "." << std::endl;
			hp = std::min(maxHP, hp + ammount);
		}

		virtual void lastRites() { }
		std::string name() { return name_; }
		bool alive() { return (hp > 0); }
		virtual void defenseMode() { defending = true; }
		std::reference_wrapper<Point> pos() { return coordinate; }
};

Point Entity::graveyard = Point(100, 100);