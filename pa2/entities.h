#pragma once

//#include <vector>

#include "entity.h"
#include "types.h"
#include "stuff.h"

class Palico;

class Monster : public Entity {
public:
	Monster(Point point) : Entity(100, 20, 1, point)
	{
		
	}

	Monster(std::string fname, std::string lname, std::string gender_, int age_) : Entity(100, 20, 1, Point(0,0))
	{
		fName = fname;
		lName = lname;
		gender = gender_;
		age = age_;
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
	int energy;
	bool champion = false;
	Sword sword = Sword(5);
	Equipment equip = Equipment(5);

	Hunter(Point point) : Entity(100, 10, 4, point)
	{
		atk += sword.atk;
		def += equip.def;
	}

	Hunter(std::string fname, std::string lname, std::string gender_, int age_, int energy_, int HP, int attack, int defence, Sword sw, Equipment eq) : Entity(100, 10, 4, Point(0,0))
	{
		fName = fname;
		lName = lname;
		gender = gender_;
		age = age_;
		energy = energy_;
		maxHP = HP;
		sword = sw;
		equip = eq;
		atk = attack + sword.atk;
		def = def + eq.def;
	}

	virtual std::string typeName() override { return "Hunter "; }

	void setPartner(Palico* p)
	{
		def *= 1.5;
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
	Equipment equip = Equipment(5);
	Sword sword = Sword(5);

	Palico(Point point) : Entity(50, 5, 0, point)
	{		
		atk += sword.atk;
		def += equip.def;
	}

	Palico(std::string name_, int age_, std::string gender_, int maxHP_, int attack, Sword sw) : Entity(50, 5, 0, Point(0,0))
	{
		name = name;
		gender = gender_;
		maxHP = maxHP_;
		atk = attack;
		sword = sw;
		atk += sword.atk;
	}


	virtual std::string typeName() override { return "Palico "; }

	void setPartner(Hunter& h)
	{
		std::cout << "Palico " << name << " forms Champion duo with Hunter " << h.name << std::endl;
		champion = true;
		atk*=1.5;
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
			atk/=1.5;
			champion = false;
			partner->champion = false;
		}
	}

	virtual void draw() override
	{
		if (champion)
		{
			GFX::drawLargeCircle(coordinate.x, coordinate.y, color);
			GFX::drawSmallSquare(coordinate.x, coordinate.y, partner->color);
		}
		else
			GFX::drawCircle(coordinate.x, coordinate.y, color);
	}
};