
#ifndef hDeck
#define hDeck

#include "Card.h"
#include "Hand.h"
#include "GenericPlayer.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class Deck : public Hand
{
public:
	Deck();

	virtual ~Deck();

	//create a standard deck of 52 cards
	void Populate();

	//shuffle cards
	void Shuffle();

	//deal one card to a hand
	void Deal(Hand& aHand);

	//give additional cards to a generic player 
	void AdditionalCards(GenericPlayer& aGenericPlayer);
};

#endif
