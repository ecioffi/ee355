#include <iostream>

using namespace std;

unsigned int fib(unsigned int n)
{
	if (n == 0 || n == 1)
		return n;
	return fib(n - 1) + fib(n - 2);
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "USEAGE: " << argv[0] << " num" << endl;
		return 1;
	}

	unsigned int num = atoi(argv[1]);

	unsigned int f = 0;
	unsigned int n = 0;
	while (f <= num)
	{

		if (f == num)
		{
			cout << "1" << endl;
			return 0;
		}
		n++;
		f = fib(n);
	}
	if ((f - num) < (num - fib(n - 1)))
	{
		cout << "0" << endl << f << endl;
		return 0;
	}
	else
	{
		cout << "0" << endl << fib(n - 1) << endl;
		return 0;
	}
}