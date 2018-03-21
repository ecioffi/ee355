#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#define n 5
#define m 5

int main()
{
	// init everything
	int A[n][m] = {};
	
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			A[i][j] = rand() % 10;
		}
	}

	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			sum += A[i][j];
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			A[i][j] = sum - A[i][j];
		}
	}

	return 0;
}