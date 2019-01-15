/*
#include <iostream>
#include <string>
using namespace std;

int main()
{
	enum difficulty { Easy = 1, Normal, Hard };

	cout << "Easy - " << Easy << endl;
	cout << "Normal - " << Normal << endl;
	cout << "Hard - " << Hard << endl;
	cout << endl;

	int choice;
	string choice2;

	cout << "Choice: ";
	cin >> choice;
	cout << "You picked: " << endl;

	difficulty myDifficulty = (difficulty)choice;

	switch (choice)
	{
	case Easy:
		choice2 = "Easy";
		break;
	case Normal:
		choice2 = "Normal";
		break;
	case Hard:
		choice2 = "Hard";
		break;
	}

	cout << choice2 << endl;
	return 0;
}
*/