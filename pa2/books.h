#pragma once

#include <list>

#include "entities.h"

template <class T> class Book {
public:
	std::list<T> list;
};

class HunterBook : public Book<Hunter> {

};

class PalicoBook : public Book<Palico> {

};

class MonsterBook : public Book<Monster> {

};