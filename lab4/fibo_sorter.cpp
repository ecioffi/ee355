#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

// generatea fib numbers upto n into a dynamic array, returns pointer to
uint64_t* genFibs(int n)
{
	uint64_t* fibs = new uint64_t[n]();
	uint64_t f1 = 0, f2 = 1, f = 0;
	for (int i = 0; i < n; i++)
	{
		f = f1 + f2;
		f1 = f2;
		f2 = f;
		fibs[i] = f1;
	}

	return fibs;
}

class FibArray2D {
public:
	int n; // dimension of the square array M
	int N; // number of elements in M
	int c; // current fib. number to be placed in M

	uint64_t** M; // content of the array M
	uint64_t* fibs; // array of fib. numbers

	// places the current fib. number in M at given location, increments c
	void place(int i, int j)
	{

		M[i][j] = fibs[c];
		c--;
	}

	// crawls a diag from a start square going down and left.
	void crawlDiagonal(int i, int j)
	{
		while (i >= 0 && j < (n - 1))
		{
			place(i, j);
			i--;
			j++;
		}
	}
	
	FibArray2D(int s)
	{
		n = ceil(sqrt(s)); // M myst be square but big enough to hold s fib numbers
		c = s - 1; // arrays index from 0, so start placing fib. numbers at fibs[s-1]
		M = new uint64_t*[n]; // M has dimenson n
		fibs = genFibs(s); // generate all needed fibs

		// init array
		for (int i = 0; i < n; i++)
			M[i] = new uint64_t[n]();

		// place diags (except y=n-1 row):
		// place main diagonol
		for (int i = n; i > 1; i--)
			place(i - 1, n - i);

		// place x diags
		for (int i = 0; i < n - 1; i++)
			crawlDiagonal(i, 0);

		// place y diags
		for (int j = 1; j < n; j++)
			crawlDiagonal(n - 1, j);

		// place remaining fibs on y=n-1 row
		for (int i = n-1; i >= 0 && c >= 0; i--)
			if (M[i][n-1] == 0)
				place(i, n-1); // if square has 0, place a fib 

			delete[] fibs; // delete dynamic fibs array
		}

		// cleanup dynamic M
		~FibArray2D()
		{
			for (int i = 0; i < n; i++)
				delete[] M[i];
			delete[] M;
		}

		// print M in accordance with mapping directives
		void print()
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					cout << M[j][i] << (j == (n - 1)? "" : ","); // omit comma separator if last in row
				}
				cout << endl;
			}
		}
	};

	int main(int argc, char *argv[])
	{
		if (argc < 2)
		{
			cout << "USEAGE: " << argv[0] << " N (0 <= N <= 80)" << endl;
			return 1;
		}
		int num = min(max(stoi(argv[1]), 0), 80); // s is min 0, max 80

		// open output file
		ofstream out;
  		out.open ("output.txt");
  		// save old stream and redirect cout to out file
		auto coutbuf = cout.rdbuf(out.rdbuf());

		if (num == 0) // if s=0 just return becaue M would be empty
			return 0;
		if (num == 1) // if s=1 just print "1" because M is "1"
		{
			cout << "1" << endl;
			return 0;
		}

		FibArray2D fa(num); // create properly ordered M
		fa.print(); // print it

		cout.rdbuf(coutbuf); // return cout to default stream
		return 0;
	}