#include<iostream>
#include <fstream>

#include "books.h"

int HunterBook::s = 0;

bool operator<(const Hunter& l, const Hunter& r)
{
	if (HunterBook::s == 0)
		return l.energy < r.energy;
	else if (HunterBook::s == 1)
		return l.maxHP < r.maxHP;
	else if (HunterBook::s == 2)
		return l.atk < r.atk;
	else
		return l.def < r.def;
}

bool operator==(const Hunter& l, const Hunter& r)
{
	return (l.energy == r.energy) && (l.maxHP == r.maxHP) && (l.atk == r.atk) && (l.def == r.def);
}

void HunterBook::sort(int S)
{
	HunterBook::s = S;
	book.sort();
}

Hunter HunterBook::getMax(int S)
{
	sort(S);
	book.reverse();
	return book.front();
}

void HunterBook::add(std::string fname, std::string lname, std::string gender_, int age_, int energy_, int HP, int attack, int defence, Sword sw, Equipment eq)
{
	book.emplace_front(fname, lname, gender_, age_, energy_, HP, attack, defence, sw, eq);
	book.sort();
	book.unique();
}

void HunterBook::remove(std::string fName)
{
	book.remove_if([fName](Hunter& h) { return h.fName == fName; });
}

void HunterBook::save()
{
	std::ofstream f;
	f.open("Hunter.txt");
	for (auto& h : book)
	{
		f << h.fName << " " << h.lName << ", " << h.age << "Energy: " << h.energy << ", " << "HP: " << h.maxHP << "Attack: " << h.atk << ", Defence: ";
		f << h.def << ", Sword: " << h.sword.name << "(" << h.sword.atk << "), Equipment: " << h.equip.name << "(" << h.equip.def << ")" << std::endl;
	}
	f.close();
}

void HunterBook::search(std::string fName)
{
	for (auto& a : book)
	{
		if (a.fName == fName)
		{
			std::cout << a.fName << " " << a.lName << ", " << a.gender << ", " << a.age << std::endl;
		}
		else
		{
			std::cout << "not found" << std::endl;
		}
	}
}