#include <iostream>
#include<vector>
#include<list>

using namespace std;

int num = 0;

class Person {
private:
	int ssn;
	string firstLastName;
public:
	Person(int ssn_, string firstLastName_) : ssn(ssn_), firstLastName(firstLastName_) { }
	string getName() { return firstLastName; }
	int getSSN() { return ssn; }
};

class USCAlum : public Person {
public:
	USCAlum(int ssn_, string firstLastName_) : Person(ssn_, firstLastName_)
	{
		num++;
		cout << "You are USC Alumnus No. " << num << endl;
	}
};

class TeslaEmployee : public Person {
private:
	vector<Person> contacts;
public:
	TeslaEmployee(int ssn_, string firstLastName_) : Person(ssn_, firstLastName_) { }
};

class IntfCarOwner {
public:
	IntfCarOwner() { }

	virtual void PrintCarInfo();
};

vector<USCAlum> uscAlums;
list<TeslaEmployee> teslaEmployees;

void check58()
{
	for (auto e : teslaEmployees)
	{
		if (to_string(e.getSSN()).find("58") != string::npos)
		{
			cout << "TeslaEmployee " << e.getName() << " with SSN: " << e.getSSN() << endl;
		}
	}
}

bool checkSSNTesla(int ssn)
{
	for (auto e : teslaEmployees)
	{
		if (e.getSSN() == ssn)
			return true;
	}

	return false;
}

bool checkSSNUSC(int ssn)
{
	for (auto a : uscAlums)
	{
		if (a.getSSN() == ssn)
			return true;
	}

	return false;
}

void USCTeslaCommon()
{
	for (auto a : uscAlums)
	{
		if (checkSSNTesla(a.getSSN()))
			cout << "Person " << a.getName() << " with SSN: " << a.getSSN() << " is in both databases." << endl;
	}
}

int main(int argc, char *argv[])
{
	string name;
	int ssn;

	for (int i = 0; i < 10; i++)
	{
		name = "";
		while (name == "")
		{
			cout << "Please enter USCAlum # " << i+1 << "'s name." << endl;
			cin >> name;
		}

		ssn = 0;
		while (ssn == 0)
		{
			cout << "Please enter USCAlum # " << i+1 << "'s SSN." << endl;
			cin >> name;
			ssn = stoi("0" + name);
			// CORNER CASE: check for non-valid SSN being entered
			if (to_string(ssn).size() != 9)
			{
				cout << "Error: Invlaid SSN." << endl;
				ssn = 0;
			}
			//CORNER CASE: check for duplicate SSN
			if (checkSSNUSC(ssn))
			{
				cout << "Error: SSN already in use." << endl;
				ssn = 0;
			}
		}

		uscAlums.push_back(USCAlum(ssn, name));
	}

	for (int i = 0; i < 15; i++)
	{
		name = "";
		while (name == "")
		{
			cout << "Please enter TeslaEmployee # " << i+1 << "'s name." << endl;
			cin >> name;
		}

		ssn = 0;
		while (ssn == 0)
		{
			cout << "Please enter TeslaEmployee # " << i+1 << "'s SSN." << endl;
			cin >> name;
			ssn = stoi("0" + name);
			// CORNER CASE: check for non-valid SSN being entered
			if (to_string(ssn).size() != 9)
			{
				cout << "Error: Invlaid SSN." << endl;
				ssn = 0;
			}
			//CORNER CASE: check for duplicate SSN
			if (checkSSNTesla(ssn))
			{
				cout << "Error: SSN already in use." << endl;
				ssn = 0;
			}
		}

		teslaEmployees.push_back(TeslaEmployee(ssn, name));
	}

	check58();
	return 0;
}

/*
NOTES: compile with --std=c++11

Corner cases accounted for are:
	- invalid SSN entered (ie not 9 digits). It also ignores non digit chars.
	- duplicate SSN entered (ie belongs to another person in the same database)
*/