#include <iostream>
#include <random>
#include <functional>

using namespace std;

std::random_device rnd;
std::mt19937 gen(rnd());
uniform_int_distribution<int> dist(0,9999);
auto rand4d = bind(dist, gen);

class Person {
public:
	char Name[10];
	int Num;
	Person() { }
	Person(const char name[], int num) : Num(num) { copy(name, name + 10, begin(Name)); }

	void Print_Name() { cout << Name << endl; }
	void Set_Name(string name) { name.copy(Name, 10, 0); }
	static bool Is_Winner(Person& p) { return (p.Num < 2020); }

};

void playGame()
{
	Person* person = new Person[3];
	cout << "Welcome to the lottery game!" << endl;
	for (int i = 0; i < 3; i++)
	{
		string in = "";
		while (in.length() == 0 || in.length() > 10)
		{
			cout << "Enter Player " << i+1 << " name (max 10 characters) :" << endl;
			cin >> in;
		}
		person[i] = Person(in.c_str(), rand4d());
	}

	for (int i  = 0; i < 3; i++)
	{
		if (Person::Is_Winner(person[i]))
		{
			cout << "Zdrastvuy!!! Concratulations " << person[i].Name << "! Your number " << person[i].Num << " is a winner. Your grand prize is on the way." << endl;
		}
		else
		{
			cout << "Shootrastvuy!! I'm sorry " << person[i].Name << ". Maybe next time in 2024!" << endl;
		}
	}

	delete[] person;
}

int main(int argc, char *argv[])
{
	playGame();
	while (true)
	{
		string in = "";
		while (in != "Yes" && in != "No")
		{
			cout << "Play again? (Yes/No)" << endl;
			cin >> in;
		}
		if (in == "No")
			exit(0);
		playGame();
	}
	return 0;
}
