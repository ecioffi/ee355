
//Program to calculate years taken to reach target balance. 
//But it gives 1 year as result for any value of balance or target.

#include <iostream>

using namespace std;

int main()
{ 
	int balance=200;
	int target=1000;
	float rate = 0.1;
	int year = 0;
	do
	{
		float interest = balance * rate;
		balance = balance + interest;
		year++;
	} while ( balance <= target );
	cout << year << "No. of years to achieve target balance.\n";
	return 0;
}
