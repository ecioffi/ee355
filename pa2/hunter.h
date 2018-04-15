#pragma once

//#include <vector>

#include "entity.h"
#include "types.h"

class Hunter : public Entity {
private:
	int stamina = 100;

public:
	//static std::vector<Hunter> hunterBook;

	Hunter(Point point) : Entity(100, 10, 4, point)
	{
		
	}

	virtual void draw() const override
	{
		GFX::drawSquare(coordinate.x, coordinate.y, color);
	}
};