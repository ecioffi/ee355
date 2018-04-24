#include <iostream>
#include <algorithm>
#include <fstream>

#include "books.h"

int PalicoBook::mode = 0;

PalicoBook::PalicoBook()
{
	std::make_heap(book.begin(), book.end());
}

bool operator<(const Palico& l, const Palico& r)
{
	if (PalicoBook::mode == 0)
		return l.atk < r.atk;
	else
		return l.maxHP < r.maxHP;
}

void PalicoBook::changeMode(int hp_attack)
{
	PalicoBook::mode = hp_attack;
	std::sort_heap(book.begin(), book.end());
}

void PalicoBook::add(Palico p)
{
	book.push_back(p);
	std::push_heap(book.begin(), book.end());
}

Palico* PalicoBook::max(int hp_attack)
{
	if (hp_attack != PalicoBook::mode)
	{
		PalicoBook::mode ^= 1;
		std::sort_heap(book.begin(), book.end());
		Palico& ret = book.front();
		PalicoBook::mode ^= 1;
		std::sort_heap(book.begin(), book.end());
		return &ret;
	}
	return &book.front();
}

void PalicoBook::remove(std::string name)
{
	for (auto it = book.begin(); it != book.end(); )
	{
		if (it->name == name)
		{
			book.erase(it);
			return;
		}
		else
            ++it;
    }
	std::cout << name << " not in heap" << std::endl;
}

void PalicoBook::search(std::string name)
{
	for (auto& p : book)
	{
		if (p.name == name)
		{
			std::cout << p.name << ", " << p.gender << ", " << p.age << ", " << "HP: " << p.maxHP << ", " << "Attack: " << p.atk << ", ";
			std::cout << "Sword: " << p.sword.name << "(" << p.sword.atk << ")" << std::endl;
			return;
		}
	}
	std::cout << name << " not in heap" << std::endl;
}

void PalicoBook::save()
{
	std::ofstream f;
	f.open("Palico.txt");
	for (auto& p : book)
	{
		f << p.name << ", " << p.gender << ", " << p.age << ", " << "HP: " << p.maxHP << ", " << "Attack: " << p.atk << ", ";
		f << "Sword: " << p.sword.name << "(" << p.sword.atk << ")" << std::endl;
	}
	f.close();
}