#pragma once

#include <cmath>

#include "entity.h"
#include "hunter.h"

class Palico : public Entity {
	public:
		Palico() : Entity("Palico", 50, 5, 0) { }

		void healEntity(Entity& friendly)
		{
			std::cout << name_ << " heals " << friendly.name() << "!" << std::endl;
			heal(5);
			friendly.heal(5);
		}

		void lastRites()
		{
			std::cout << "Rathalos killed your cat!!!!!" << std::endl;
		}

		void defenseMode() { }
};