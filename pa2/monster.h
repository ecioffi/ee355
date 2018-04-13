#pragma once

#include "entity.h"

class Monster : public Entity {
	public:
		Monster() : Entity("Rathalos", 100, 20, 1) { }

		void lastRites()
		{
			std::cout << "\nCongratulations! The corpse should frieghten the other Rathalos away from here." << std::endl;
		}
};