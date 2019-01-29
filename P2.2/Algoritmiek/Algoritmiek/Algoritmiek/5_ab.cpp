
#include <iostream>
#include <algorithm>
#include <map>
#include <limits>
#include "ttt.h"

using namespace std;
using MoveEval = std::pair<int, int>;

enum class PlayerType
{
	Human,
	Computer
};

int findScores(const State &board, const Player &winner)
{
	array<int, 9> subscores = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (int i = 0; i < 9; i++)
	{
		if (winner == Player::X)
		{
			if (board[i] == Player::X)
			{
				subscores[i] += 10;
			}

			if (board[i] == Player::O)
			{
				subscores[i] -= 10;
			}
		}

		if (winner == Player::O)
		{
			if (board[i] == Player::X)
			{
				subscores[i] -= 10;
			}

			if (board[i] == Player::O)
			{
				subscores[i] += 10;
			}
		}
	}

	int score = 0;

	for (int i = 0; i < 9; i++)
	{
		score += subscores[i];
	}

	return score;
}

int eval(const State &board, const Player &player)
{
	return findScores(board, player);
}

MoveEval alphaBeta(State &board, int ply, Player player, Player opponent, int alpha, int beta)
{
	if (ply == 0)
		return std::make_pair(Move(), eval(board, player));

	std::vector<Move> moves = getMoves(board);
	if (moves.size() == 0)
		return std::make_pair(Move(), eval(board, player));

	MoveEval best = std::make_pair(Move(), alpha);
	for (Move &move : moves)
	{
		State nb = doMove(board, move);
		MoveEval me = alphaBeta(nb, ply - 1, opponent, player, -beta, -alpha);

		if (-me.second > alpha)
		{
			alpha = -me.second;
			best = std::make_pair(move, alpha);
		}
		if (alpha >= beta)
			return best;
	}
	return best;
}

Move alphaBeta(const State &b, int ply)
{
	State board(b);
	Player player = getCurrentPlayer(board);
	Player opponent = Player::None;

	if (player == Player::X)
		opponent = Player::O;
	else
		opponent = Player::X;

	return alphaBeta(board, ply, player, opponent, std::numeric_limits<int>::min() + 1, std::numeric_limits<int>::max()).first;
}

int main()
{
	std::srand(std::time(0));

	std::map<Player, PlayerType> playerType;
	playerType[Player::X] = PlayerType::Human;
	playerType[Player::O] = PlayerType::Computer;

	State board = {
			Player::None, Player::None, Player::None,
			Player::None, Player::None, Player::None,
			Player::None, Player::None, Player::None};
	std::cout << board << std::endl;

	std::vector<Move> moves = getMoves(board);
	while (moves.size() > 0)
	{
		if (playerType[getCurrentPlayer(board)] == PlayerType::Human)
		{
			std::cout << "+-+-+-+" << std::endl
								<< "|0|1|2|" << std::endl
								<< "+-+-+-+" << std::endl
								<< "|3|4|5|" << std::endl
								<< "+-+-+-+" << std::endl
								<< "|6|7|8|" << std::endl
								<< "+-+-+-+" << std::endl
								<< std::endl;
			std::cout << "Enter a move ( ";
			for (Move m : moves)
				std::cout << m << " ";
			std::cout << "): ";
			Move m;
			std::cin >> m;
			board = doMove(board, m);
		}
		else
		{
			board = doMove(board, alphaBeta(board, 9));
		}
		std::cout << board << std::endl;
		moves = getMoves(board);
	}

	return 0;
}
