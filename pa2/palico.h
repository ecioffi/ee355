#pragma once

#include <cmath>

#include "entity.h"
#include "hunter.h"

class Palico : public Entity {
	public:
		Palico(Point point) : Entity(50, 5, 0, point)
		{
			
		}

		virtual void draw() const override
		{
			GFX::drawCircle(coordinate.x, coordinate.y, color);
		}

		void healEntity(Entity& friendly)
		{
			std::cout << name_ << " heals " << friendly.name() << "!" << std::endl;
			heal(5);
			friendly.heal(5);
		}
};