#pragma once

#include <list>
#include <forward_list>
#include <vector>

#include "entities.h"


class HunterBook {
public:
	std::forward_list<Hunter> book;
	std::forward_list<Hunter>& data() { return book; }
	static int s;

	void add(std::string fname, std::string lname, std::string gender_, int age_, int energy_, int HP, int attack, int defence, Sword sw, Equipment eq);
	void add(Point p);
	void sort(int S);
	Hunter getMax(int S);
	void remove(std::string fName);
	void save();
	void search(std::string fName);
};

class MonsterBook{
public:
	std::list<Monster> book;
	std::list<Monster>& data() { return book; }

	void add(std::string fname, std::string lname, std::string gender_, int age_);
	void add(Point p);
	void remove(std::string fName);
	void save();
	void search(std::string fName);
};

class PalicoBook {
public:
	static int mode;

	std::vector<Palico> book;	
	std::vector<Palico>& data() { return book; }

	PalicoBook();

	void changeMode(int hp_attack);
	void add(std::string name_, int age_, std::string gender_, int maxHP_, int attack, Sword sw);
	void add(Point p);
	Palico* max(int hp_attack);
	void remove(std::string name);
	void search(std::string name);
	void save();
};