#pragma once

#include "card.h"

class Deck
{
public:
	Deck();
	~Deck();

private:
	Card cards[52];
};