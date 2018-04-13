#include <iostream>
#include <string>
#include <random>
#include <functional>
#include <chrono>

#include "hunter.h"
#include "monster.h"
#include "palico.h"

using namespace std;

Hunter hunter = Hunter();
Palico palico = Palico();
Monster monster = Monster();
int kills = 0;

std::random_device rnd;
std::mt19937 gen(rnd());
uniform_int_distribution<int> dist(1,10);
auto deciRand = bind(dist, gen);

bool inBounds(int value, int low, int high)
{
	return (low <= value) && (value <= high);
}

void pause(std::string message)
{
	std::chrono::duration<double> elapsed(0);

	cout << message << endl;
	while (chrono::duration_cast<chrono::milliseconds>(elapsed).count() < 100)
	{
		auto start = chrono::high_resolution_clock::now();
		cin.ignore();
		auto end = chrono::high_resolution_clock::now();
		elapsed += end-start;
	}
}

void pause() { pause(""); }

void queryAorD()
{
	string in = "";
	while (!inBounds(stoi("0" + in), 1, 2))
	{
		cout << "You face the charging monster, and:\n\t" <<
				"Attack (1)\n\t" <<
				"Defend (2)" << std::endl;
		cin >> in;
	}

	if (stoi("0" + in) == 1)
		hunter.attack(monster);
	else
		hunter.defenseMode();
}

void queryPalico()
{
	if (!palico.alive())
		return;

	string in = "";
	while (!inBounds(stoi("0" + in), 1, 2))
	{
		cout << "In the midst of battle, your Palico:\n\t" <<
				"Jumps in and attacks (1)\n\t" <<
				"Heals you            (2)" << endl;
		cin >> in;
	}

	if (stoi("0" + in) == 1)
		palico.attack(monster);
	else
		palico.healEntity(hunter);

}

void chanceMonsterAN()
{
	cout << "The Rathalos stares you down and..." << endl;
	pause();
	int c = deciRand();

	if (inBounds(c, 1, 2) && palico.alive())
		monster.attack(palico);
	else if (inBounds(c, 3, 9))
		monster.attack(hunter);
	else
		cout << "Strangely, he does nothing." << endl;
}

void fightMonster()
{
	monster = Monster();
	cout << "A Rathalos appears!" << endl;
	while(true)
	{
		queryAorD();
		if (!monster.alive())
			break;
		queryPalico();
		if (!monster.alive())
			break;
		chanceMonsterAN();
	}
	hunter.killMonster();
	pause("Press 'Enter' to continue...");
}

void chanceMonster()
{
	if (inBounds(deciRand(), 3, 10))
	{
		fightMonster();
	}
	else
	{
		cout << "There are no Rathalos in the vicinity." << endl;
		pause("Press 'Enter' to continue...");
	}
}

int main(int argc, char const *argv[])
{
	cout << "\033c" <<
			"Welcome to the text-based monster-hunter world!\n" << 
			"Your party, a hunter and his cat, Palico, are tasked to kill as many Rathalos as possible." << endl;
	pause("Press 'Enter' to continue...");

	while (true)
	{
		string in = "";
		while (stoi("0" + in) < 1 || stoi("0" + in) > 4)
		{
			cout << "\033c";
			hunter.printStatus();
			cout << "You are walking in search of Rathalos:\n\t" <<
					"North (1)\n\t" <<
					"South (2)\n\t" <<
					"East  (3)\n\t" <<
					"West  (4)" << endl;
			cin >> in;
		}

		Cardinal c = static_cast<Cardinal> (stoi("0" + in) - 1);
		if (!hunter.walk(c))
		{
			chanceMonster();
		}
		else
		{
			if (hunter.killedMonster())
			{
				cout << "You have been here before...";
				cout.flush();
				pause();
				cout << "The stench of the slain Rathalos scares the others away...." << endl;
				pause();
			}
			else 
			{
				cout << "You have been here before..." << endl;
				pause();
				chanceMonster();
			}
		}
	}
}