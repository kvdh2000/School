
#include <iostream>
#include <algorithm>
#include <map>
#include <limits>
#include "ttt.h"

#define MIN std::numeric_limits<int>::min() + 1
#define MAX std::numeric_limits<int>::max()

unsigned const n_trials = 1000;

enum class PlayerType { Human, Computer };

using Rating = std::tuple<int, Move>;

int getRandomEval(const State &board, Player) {
	return rand() % 101 - 50;
}

int eval(const State &board, Player player) {
	auto moves = getMoves(board);
	int wins = 0;

	for (int i = 0; i < n_trials; ++i) {
		State mcBoard = board;

		std::random_shuffle(moves.begin(), moves.end());
		for (const Move &m : moves) mcBoard = doMove(mcBoard, m);

		if (getWinner(mcBoard) == player) wins++;
	}

	return wins - n_trials / 2;
}


Rating alphaBeta(const State &board, int ply, Player player, int min = MIN, int max = MAX) {
	auto moves = getMoves(board);
	Rating bestRating = std::make_tuple(min, Move());

	if (!ply || !moves.size()) return std::make_tuple(eval(board, player), Move());

	for (Move &m : moves) {
		Rating rating;
		Player other = player == Player::O ? Player::X : Player::O;

		rating = alphaBeta(doMove(board, m), ply - 1, other, -max, -min);

		if (-std::get<0>(rating) > min) {
			min = -std::get<0>(rating);
			bestRating = std::make_tuple(min, m);
		}

		if (min >= max) return bestRating;
	}

	return bestRating;
}

int main() {
	std::srand(std::time(0));

	std::map<Player, PlayerType> playerType;
	playerType[Player::X] = PlayerType::Human;
	playerType[Player::O] = PlayerType::Computer;

	State board = {
		Player::None, Player::None, Player::None,
		Player::None, Player::None, Player::None,
		Player::None, Player::None, Player::None };
	std::cout << board << std::endl;

	std::vector<Move> moves = getMoves(board);
	while (moves.size() > 0) {
		if (playerType[getCurrentPlayer(board)] == PlayerType::Human) {
			std::cout << "+-+-+-+" << std::endl <<
				"|0|1|2|" << std::endl <<
				"+-+-+-+" << std::endl <<
				"|3|4|5|" << std::endl <<
				"+-+-+-+" << std::endl <<
				"|6|7|8|" << std::endl <<
				"+-+-+-+" << std::endl << std::endl;
			std::cout << "Enter a move ( ";
			for (Move m : moves) std::cout << m << " ";
			std::cout << "): ";
			Move m;
			std::cin >> m;
			board = doMove(board, m);
		}
		else {
			Rating r = alphaBeta(board, 5, getCurrentPlayer(board));
			std::cout << std::get<1>(r);
			std::cout << " (";
			std::cout << std::get<0>(r);
			std::cout << ")";
			std::cout << std::endl;
			board = doMove(board, std::get<1>(r));
		}
		std::cout << board << std::endl;
		moves = getMoves(board);
	}

	return 0;
}