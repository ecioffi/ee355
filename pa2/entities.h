#pragma once

//#include <vector>

#include "entity.h"
#include "types.h"

class Palico;

class Monster : public Entity {
public:
	Monster(Point point) : Entity(100, 20, 1, point)
	{
		
	}

	virtual std::string typeName() override { return "Monster "; }

	virtual void interact(std::list<std::reference_wrapper<Entity>>& entities) override
	{
		if (dead())
			return;
		for (auto& e : entities)
		{
			if (e.get().coordinate != coordinate)
				continue;
			if (e.get().alive() && typeid(e.get()) != typeid(Monster))
				battle(e);
		}
	}

	virtual void draw() override
	{
		GFX::drawTriangle(coordinate.x, coordinate.y, color);
	}
};

class Hunter : public Entity {
private:
	int stamina = 100;
	Palico* partner;

public:
	bool champion = false;

	Hunter(Point point) : Entity(100, 10, 4, point)
	{
		
	}

	virtual std::string typeName() override { return "Hunter "; }

	void setPartner(Palico* p)
	{
		champion = true;
		partner = p;
	}

	virtual void divorce() override;

	virtual void interact(std::list<std::reference_wrapper<Entity>>& entities) override
	{
		if (dead())
			return;
		for (auto& e : entities)
		{
			if (e.get().coordinate != coordinate)
				continue;
			if (e.get().alive() && typeid(e.get()) == typeid(Monster))
				battle(e);
		}
	}

	virtual void move() override
	{
		if (champion)
			return;

		Cardinal c = randCardinal();
		while ((coordinate + c).outOfBounds())
			c = randCardinal();
		
		coordinate += c;
	}

	virtual void lastRites() override
	{
		if (champion)
			divorce();
	}

	virtual void draw() override
	{
		if (!champion)
		{
			GFX::drawSquare(coordinate.x, coordinate.y, color);
		}
	}
};

class Palico : public Entity {
private:
	Hunter* partner;
public:
	bool champion = false;

	Palico(Point point) : Entity(50, 5, 0, point)
	{

	}

	virtual std::string typeName() override { return "Palico "; }

	void setPartner(Hunter& h)
	{
		std::cout << "Palico " << name_ << " forms Champion duo with Hunter " << h.name() << std::endl;
		champion = true;
		partner = &h;
		h.setPartner(this);
	}

	virtual void interact(std::list<std::reference_wrapper<Entity>>& entities) override
	{
		if (dead())
			return;

		for (auto& ex : entities)
		{
			Entity& e = ex.get();
			if (e.coordinate != coordinate)
				continue;
			if (alive())
			{
				if (typeid(e) == typeid(Hunter) && !champion && !dynamic_cast<Hunter&>(e).champion)
					setPartner(dynamic_cast<Hunter&>(e));
				else if (typeid(e) == typeid(Monster))
					battle(e);
			}
		}
	}

	virtual void move() override
	{
		Cardinal c = randCardinal();
		while ((coordinate + c).outOfBounds())
			c = randCardinal();
		
		coordinate += c;
		if (champion)
			partner->coordinate += c;
	}

	virtual void lastRites() override
	{
		if (champion)
		{
			champion = false;
			partner->champion = false;
		}
	}

	virtual void draw() override
	{
		if (champion)
		{
			GFX::drawLargeCircle(coordinate.x, coordinate.y, color);
			GFX::drawSmallSquare(coordinate.x, coordinate.y, partner->getColor());
		}
		else
			GFX::drawCircle(coordinate.x, coordinate.y, color);
	}
};

void Hunter::divorce()
{
	partner->champion = false;
	champion = false;
}

Point Entity::graveyard = Point(100, 100);