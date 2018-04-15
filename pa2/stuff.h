#pragma once

#include <string>

class Item {
protected:
	std::string name;
public:
	Item(std::string name_) : name(name_) { }
};

class Sword : public Item {
private:
	int atk;
public:
	Sword(int attack) : Item("Sword"), atk(attack) { }
};

class Equipment : public Item {
private:
	int def;
public:
	Equipment(int defence) : Item("Equipment"), def(defence) { }
};