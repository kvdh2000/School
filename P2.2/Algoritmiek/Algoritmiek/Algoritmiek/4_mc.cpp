#include "4.h"
#include <iostream>
#include <algorithm>
#include <map>


using namespace std;

unsigned const n_trials = 1000;
unsigned const mc_match = 1;
unsigned const mc_other = 1;
array<int, 9> scores = { 0,0,0,0,0,0,0,0,0 };

enum class PlayerType { Human, Computer };

void mcUpdateScores(array<int, 9> &subscores, State &trialboard, Player &winner)
{
	for (int i = 0; i < 9; i++)
	{
		if (winner == Player::X)
		{
			if (trialboard[i] == Player::X)
			{
				subscores[i]++;
			}

			if (trialboard[i] == Player::O)
			{
				subscores[i]--;
			}
		}

		if (winner == Player::O)
		{
			if (trialboard[i] == Player::X)
			{
				subscores[i]--;
			}

			if (trialboard[i] == Player::O)
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

State mcTrial(const State &board)
{
	State trialboard = board;
	array<int, 9> subscores = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	Player winner;

	vector<Move> moves = getMoves(trialboard);
	
	while (moves.size() != 0) 
	{
		trialboard = doMove(trialboard, moves[(rand() % moves.size())]);
		moves = getMoves(trialboard);
	}

	winner = getWinner(trialboard);

	mcUpdateScores(subscores, trialboard, winner);


	return board;
}

Move getBestMove(State &board)
{
	int highest = -9999;
	int index = -1;

	for (int i = 0; i < 9; i++)
	{
		if (scores[i] > highest && board[i] == Player::None)
		{
			highest = scores[i];
			index = i;
		}
	}

	return index;
}

Move mcMove(State &board, const Player &player)
{
	scores = { 0,0,0,0,0,0,0,0,0 };

	for (int i = 0; i < 20; i++)
	{
		board = mcTrial(board);
	}

	return getBestMove(board);
}

int main()
{
	std::srand(std::time(0));

	std::map<Player, PlayerType> playerType;
	playerType[Player::X] = PlayerType::Human;
	playerType[Player::O] = PlayerType::Computer;

	State board =
	{
		Player::None, Player::None, Player::None,
		Player::None, Player::None, Player::None,
		Player::None, Player::None, Player::None
	};
	std::cout << board << std::endl;

	std::vector<Move> moves = getMoves(board);
	while (moves.size() > 0)
	{
		if (playerType[getCurrentPlayer(board)] == PlayerType::Human)
		{
			std::cout <<
				"+-+-+-+" << std::endl <<
				"|0|1|2|" << std::endl <<
				"+-+-+-+" << std::endl <<
				"|3|4|5|" << std::endl <<
				"+-+-+-+" << std::endl <<
				"|6|7|8|" << std::endl <<
				"+-+-+-+" << std::endl <<
				std::endl;
			std::cout << "Enter a move ( ";
			for (Move m : moves) std::cout << m << " ";
			std::cout << "): ";
			Move m;
			std::cin >> m;
			board = doMove(board, m);
		}

		else
		{
			board = doMove(board, mcMove(board, getCurrentPlayer(board)));
		}
		std::cout << board << std::endl;
		moves = getMoves(board);
	}

	return 0;
}
