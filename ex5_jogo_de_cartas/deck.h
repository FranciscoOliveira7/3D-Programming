#pragma once

#include <vector>
#include <algorithm>
#include "card.h"

using namespace std;

class Deck
{
public:
	Deck();
	~Deck();

private:
	Card cards[52];
	vector<Card> GiveDeck(int quantity);
};