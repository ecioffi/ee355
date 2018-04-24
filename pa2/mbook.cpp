#include<iostream>
#include <fstream>

#include "books.h"

bool operator<(const Monster& l, const Monster& r)
{
	return (l.fName < r.fName) || (!(l.fName < r.fName) && (l.lName < r.lName)) || (!(l.fName < r.fName) && !(l.lName < r.lName) && l.age < r.age);
}

bool operator==(const Monster& l, const Monster& r)
{
	return (l.fName == r.fName) && (l.lName == r.lName) && (l.age == r.age);
}


void MonsterBook::add(std::string fname, std::string lname, std::string gender_, int age_)
{
	book.emplace_back(fname, lname, gender_, age_);
	book.sort();
	book.unique();
}

void MonsterBook::remove(std::string fName)
{
	book.remove_if([fName](Monster& m) { return m.fName == fName; });
}

void MonsterBook::save()
{
	std::ofstream f;
	f.open("Monster.txt");
	for (auto& m : book)
	{
		f << m.fName << " " << m.lName << ", " << m.gender << ", " << m.age << std::endl;
	}
	f.close();
}

void MonsterBook::search(std::string fName)
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