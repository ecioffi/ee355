#pragma once

#include <string>

class Entity {
	protected:
		std::string name_;
		int maxHP, hp, atk, def;
		bool defending = false;
	public:
		Entity(std::string name, int HP, int attack, int defense) : name_(name), maxHP(HP), atk(attack), def(defense) { hp = maxHP; }

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
};