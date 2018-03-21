#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "USEAGE: " << argv[0] << " num" << endl;
		return 1;
	}

	unsigned int num = atoi(argv[1]);
	unsigned int f1 = 0, f2 = 1, f = 0;
	
	while (f <= num)
	{
		f = f1 + f2;
		f1 = f2;
		f2 = f;
		if (f == num)
		{
			cout << "1" << endl;
			return 0;
		}
	}
	if ((f - num) < (num - f1))
	{
		cout << "0" << endl << f << endl;
		return 0;
	}
	else
	{
		cout << "0" << endl << f1 << endl;
		return 0;
	}
}