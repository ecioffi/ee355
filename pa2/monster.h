#pragma once

#include "entity.h"

class Monster : public Entity {
public:
	Monster(Point point) : Entity(100, 20, 1, point)
	{
		
	}

	virtual void draw() const override
	{
		GFX::drawTriangle(coordinate.x, coordinate.y, color);
	}

	void lastRites()
	{
		std::cout << "\nCongratulations! The corpse should frieghten the other Rathalos away from here." << std::endl;
	}
};