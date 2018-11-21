
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int tries = 0;
int guess;
char ready;
char yhl = 'f';
int lowest = 1;
int highest = 100;

int newNmr(char c)
{
	int nmr;

	if (c == 'f')
	{
		nmr = rand() % 100 + 1;
	}

	if (c == 'h')
	{
		highest = guess;
		do
		{
			nmr = rand() % 100 + 1;
			if (nmr < highest && nmr > lowest)
			{
				return nmr;
			}
		} while (true);
	}

	if (c == 'l')
	{
		lowest = guess;
		do
		{
			nmr = rand() % 100 + 1;

			if (nmr < highest && nmr > lowest)
			{
				return nmr;
			}
		} while (true);
	}

	return nmr;
}
/*
int main()
{
	srand(static_cast<unsigned int>(time(0)));

	cout << "Welcome to Guess My Number\n\n";
	cout << "Think of a number" << endl << endl;
	cout << "Got one? (y/n)" << endl;
	cin >> ready;
	cout << endl;

	if (ready = 'y')
	{
		do
		{
			guess = newNmr(yhl);
			cout << "Is your number " << guess << endl << "[y] Yes it is" << endl << "[h] Too high" << endl << "[l] Too low" << endl << endl;
			cin >> yhl;
			cout << endl;
		} while (yhl != 'y');
	}
}
*/