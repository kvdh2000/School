/*
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void listGames(vector<string> games2)
{
	vector<string> :: iterator iter;

	cout << endl;

	for (iter = games2.begin(); iter < games2.end(); ++iter)
	{
		cout << *iter << endl;
	}
}

vector<string> pushGame(vector<string> games3)
{
	string input;
	cout << endl << "Insert the game you want listed" << endl << endl;
	cin >> input;
	games3.push_back(input);

	return games3;
}

vector<string> removeGame(vector<string> games4)
{
	vector<string> ::iterator iter;
	string input;
	string search;

	cout << endl << "Insert the game you want removed" << endl << endl;
	cin >> input;
	
	iter = find(games4.begin(), games4.end(), input);

	if (iter != games4.end())
	{
		int index = distance(games4.begin(), iter);
		games4.erase(games4.begin() + index);

		cout << endl << "Removed: " << input << " at index " << index << endl;
	}

	else
	{
		cout << endl << "Search is invalid, returning." << endl << endl;
	}

	return games4;
}

int main()
{
	vector<string> games;
	string game;
	char yn = 'n';

	cout << "Insert the first game you want listed" << endl << endl;
	cin >> game;
	games.push_back(game);

	do
	{
		cout << endl << "Do you want to list your games(l), add another game(a), remove a game(r) or quit(q)" << endl << endl;
		cin >> yn;

		if (yn == 'l')
		{
			listGames(games);
		}

		if (yn == 'a')
		{
			games = pushGame(games);
		}

		if (yn == 'r')
		{
			games = removeGame(games);
		}

	} while (yn != 'q');

	return 0;
}
*/