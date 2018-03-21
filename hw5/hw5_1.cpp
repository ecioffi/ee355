#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#define n 20

int main()
{
	// init everything
	int A[n] = {};
	int O[n] = {};

	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		A[i] = rand() % 10;
		O[i] = A[i];
	}

	// null dupes
	for (int i = 0; i < n; i++)
	{ 
		if (A[i] == A[i+1])
		{
			for (int j = i+1; j < n && A[i] == A[j]; j++)
			{
				A[j] = 0;
			}
		}
	}

	// reverse order
	for (int i = 0; i < n/2; i++)
	{
		int temp = A[i];
		A[i] = A[n - i - 1];
		A[n - i - 1] = temp;
	}

	for (int i = 0; i < n; i++)
	{
		std::cout << O[i] << ", " << A[i] << std::endl;
	}
}