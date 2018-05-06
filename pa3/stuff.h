#pragma once

#include <string>

#include "names.h"

class Item {
public:
	std::string name;
	Item() : name(randomName()) { }
};

class Sword : public Item {
public:
	int atk;
	Sword(int attack) : atk(attack) { }
};

class Equipment : public Item {
public:
	int def;
	Equipment(int defence) : def(defence) { }
};