#pragma once

//#include <vector>

#include "entity.h"
#include "types.h"

class Palico;

class Monster : public Entity {
public:
	std::string typeName = "Monster";

	Monster(Point point) : Entity(100, 20, 1, point)
	{
		
	}

	virtual bool isEnemy(Entity& e) override
	{
		return typeid(e) != typeid(this);
	}

	virtual void interact(std::list<std::reference_wrapper<Entity>>& entities) override
	{
		for (auto& e : entities)
			if (typeid(e) != typeid(this))
				battle(e);
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

class Hunter : public Entity {
private:
	int stamina = 100;
	Palico* partner;

public:
	std::string typeName = "Hunter";
	bool champion = false;

	Hunter(Point point) : Entity(100, 10, 4, point)
	{
		
	}

	void setPartner(Palico* p)
	{
		champion = true;
		partner = p;
	}

	void divorce();

	virtual bool isEnemy(Entity& e) override
	{
		return typeid(e) == typeid(Monster);
	}

	virtual void interact(std::list<std::reference_wrapper<Entity>>& entities) override
	{
		for (auto& e : entities)
		{
			if (!e.get().inYard() && typeid(e) == typeid(Monster))
				battle(e);
		}
	}

	virtual void draw() const override
	{
		GFX::drawSquare(coordinate.x, coordinate.y, color);
	}
};

class Palico : public Entity {
private:
	Hunter* partner;
public:
	std::string typeName = "Palico";
	bool champion = false;

	Palico(Point point) : Entity(50, 5, 0, point)
	{

	}

	void setPartner(Hunter& h)
	{
		champion = true;
		partner = &h;
		h.setPartner(this);
	}

	void divorce()
	{
		partner->divorce();
		champion = false;
	}

	virtual bool isEnemy(Entity& e) override
	{
		return typeid(e) == typeid(Monster);
	}

	virtual void interact(std::list<std::reference_wrapper<Entity>>& entities) override
	{
		for (auto& ex : entities)
		{
			Entity& e = ex.get();
			if (!e.inYard())
			{
				if (typeid(e) == typeid(Hunter) && !champion && !static_cast<Hunter&>(e).champion)
					setPartner(static_cast<Hunter&>(e));
				else if (typeid(e) == typeid(Monster))
					battle(e);
			}
		}
	}

	virtual void lastRites() override
	{
		if (champion)
		{

		}
	}

	virtual void draw() const override
	{
		GFX::drawCircle(coordinate.x, coordinate.y, color);
	}
};

void Hunter::divorce()
{
	
}

Point Entity::graveyard = Point(100, 100);