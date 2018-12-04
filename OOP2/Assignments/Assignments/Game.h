
#ifndef hGame
#define hGame

#include "Deck.h"
#include "House.h"
#include "Player.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class Game
{
public:
	Game(const vector<string>& names);

	~Game();

	//plays the game of blackjack    
	void Play();

	Deck m_Deck;
	House m_House;
	vector<Player> m_Players;
};

#endif
