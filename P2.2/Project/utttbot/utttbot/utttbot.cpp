// utttbot.cpp
// Aswin van Woudenberg

#include "utttbot.h"

#include <iostream>
#include <sstream>

using namespace std;

array<int, 9> scores = { 0,0,0,0,0,0,0,0,0 };
int activemb = 0;
int ex = 0;
int ey = 0;

int UTTTBot::getX(int i)
{
	if (i < 3)
		return 0;
	if (i < 6)
		return 1;
	else
		return 2;
}

int UTTTBot::getY(int i)
{
	if (i == 0 || i == 3 || i == 6)
		return 0;
	if (i ==1 || i == 4 || i == 7)
		return 1;
	else
		return 2;
}

void UTTTBot::findAMB(State &board)
{
	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			if (board.board[x][y] == Player::Active)
			{
				foundit(y, x);
				break;
			}
		}
	}
}

void UTTTBot::foundit(int x, int y)
{
	if (x < 3)
	{
		if (y < 3)
		{
			activemb = 0;
		}

		if (2 < y < 6)
		{
			activemb = 1;
		}

		if (5 < y < 9)
		{
			activemb = 2;
		}
	}

	if (2 < x < 6)
	{
		if (y < 3)
		{
			activemb = 3;
		}

		if (2 < y < 6)
		{
			activemb = 4;
		}

		if (5 < y < 9)
		{
			activemb = 5;
		}
	}

	if (5 < x < 9)
	{
		if (y < 3)
		{
			activemb = 6;
		}

		if (2 < y < 6)
		{
			activemb = 7;
		}

		if (5 < y < 9)
		{
			activemb = 8;
		}
	}

	switch(activemb)
	{
		case 0:
		{
			ex = 0;
			ey = 0;
			break;
		}

		case 1:
		{
			ex = 3;
			ey = 0;
			break;
		}
		
		case 2:
		{
			ex = 6;
			ey = 0;
			break;
		}

		case 3:
		{
			ex = 0;
			ey = 3;
			break;
		}

		case 4:
		{
			ex = 3;
			ey = 3;
			break;
		}

		case 5:
		{
			ex = 6;
			ey = 3;
			break;
		}

		case 6:
		{
			ex = 0;
			ey = 6;
			break;
		}

		case 7:
		{
			ex = 3;
			ey = 6;
			break;
		}

		case 8:
		{
			ex = 6;
			ey = 6;
			break;
		}
	}
}

void UTTTBot::run() 
{
	std::string line;

	while (std::getline(std::cin, line)) 
	{
		std::vector<std::string> command = split(line, ' ');

		if (command[0] == "settings") 
		{
			setting(command[1], command[2]);
		} 

		else if (command[0] == "update" && command[1] == "game") 
		{
			update(command[2], command[3]);
		} 

		else if (command[0] == "action" && command[1] == "move") 
		{
			move(std::stoi(command[2]));
		} 

		else 
		{
			std::cerr << "Unknown command: " << line << std::endl;
		}
	}
}


void UTTTBot::mcUpdateScores(State &trialboard, Player &winner)
{
	array<int, 9> subscores = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (int i = 0; i < 9; i++)
	{
		int x = getY(i);
		int y = getX(i);

		if (winner == Player::X)
		{
			if (trialboard.board[x + ex][y + ey] == Player::X)
			{
				subscores[i]++;
			}

			if (trialboard.board[x + ex][y + ey] == Player::O)
			{
				subscores[i]--;
			}
		}

		if (winner == Player::O)
		{
			if (trialboard.board[x + ex][y + ey] == Player::X)
			{
				subscores[i]--;
			}

			if (trialboard.board[x + ex][y + ey] == Player::O)
			{
				subscores[i]++;
			}
		}
	}


	for (int i = 0; i < 9; i++)
	{
		scores[i] = scores[i] + subscores[i];
	}
}

State UTTTBot::mcTrial(const State &board)
{
	State trialboard = board;
	
	Player winner;

	vector<Move> moves = getMoves(trialboard);

	while (moves.size() != 0)
	{
		trialboard = doMove(trialboard, moves[(rand() % moves.size())]);
		moves = getMoves(trialboard);
	}

	winner = getWinner(trialboard);

	mcUpdateScores(trialboard, winner);


	return board;
}

Move UTTTBot::getBestMove(State &board)
{
	int highest = -999999;

	int dx = -99999;
	int dy = -99999;
	
	
	for (int i = 0; i < 9; i++)
	{
		int x = getY(i);
		int y = getX(i);

		if (scores[i] > highest && board.board[x + ex][y + ey] == Player::Active)
		{
			highest = scores[i];
			dx = x + ex;
			dy = y + ey;
		}
	}

	return { dx, dy };
}

Move UTTTBot::mcMove(State &board)
{
	scores = { 0,0,0,0,0,0,0,0,0 };

	findAMB(board);

	for (int i = 0; i < 10000; i++)
	{
		board = mcTrial(board);
	}

	return getBestMove(board);
}

void UTTTBot::move(int timeout) 
{
	// Do something more intelligent here than return a random move
	//vector<Move> moves = getMoves(state);
	//moves.push_back(mcMove(state));
	Move theMove = mcMove(state);
	//std::cout << "place_disc " << *(moves.end() - 1) << std::endl;
	std::cout << "place_disc " << theMove << std::endl;
}

void UTTTBot::update(std::string &key, std::string &value) {
	if (key == "round") {
		round = std::stoi(value);
	} else if (key == "field") {
		int row = 0;
		int col = 0;
		std::vector<std::string> fields = split(value, ',');
		for (std::string &field : fields) {
			if (field == "0") {
				state.board[row][col] = Player::X; 
			} else if (field == "1") {
				state.board[row][col] = Player::O;
			} else {
				state.board[row][col] = Player::None;
			}
			col++;
			if (col == 9) {
				row++; 
				col = 0;
			}
		}
	} else if (key == "macroboard") {
		int row = 0;
		int col = 0;
		std::vector<std::string> fields = split(value, ',');
		for (std::string &field : fields) {
			if (field == "-1") {
				state.macroboard[row][col] = Player::Active;
			} else if (field == "0") {
				state.macroboard[row][col] = Player::X;
			} else if (field == "1") {
				state.macroboard[row][col] = Player::O;
			} else {
				state.macroboard[row][col] = Player::None;
			}
			col++;
			if (col == 3) {
				row++;
				col = 0;
			}
		}
	}
}

void UTTTBot::setting(std::string &key, std::string &value) {
	if (key == "timebank") {
		timebank = std::stoi(value);
	} else if (key == "time_per_move") {
		time_per_move = std::stoi(value);
	} else if (key == "player_names") {
		std::vector<std::string> names = split(value, ',');
		player_names[0] = names[0];
		player_names[1] = names[1];
	} else if (key == "your_bot") {
		your_bot = value;
	} else if (key == "your_botid") {
		your_botid = std::stoi(value);
	}
}

std::vector<std::string> UTTTBot::split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

