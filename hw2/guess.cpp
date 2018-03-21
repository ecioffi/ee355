#include <iostream>
#include <cstdlib>
#include <ctime>
int main()
{
	srand(time(0));
	int num = rand() % 20;
	int cap = (rand() % 6) + 5;
	std::cout << "Welcome to the guessing game. int x is in [0, 19]. You get " << cap  << " tries." << std::endl;
	std::cout << "Guess: ";
	for (int tries = 0; tries < cap; tries++)
	{
		int guess = 0;
		std::cin >> guess;
		if (num == guess)
		{
			std::cout << "Correct -- You win." << std::endl;
			return 0;
		}
		std::cout << "Wrong -- Try again: ";
	}
	std::cout << "You loose." << std::endl;
	return 0; 
}
