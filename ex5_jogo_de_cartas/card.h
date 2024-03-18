#pragma once

enum naipe {
	kOuros, kEspadas, kEscudos, kCopas
};

enum value {
	k2 = 2, k3 = 3, k4 = 4,
	k5 = 5, k6 = 6, k7 = 7,
	k8 = 8, k9 = 9, k10 = 10,
	kJ = 11, kQ = 12, kK = 13,
	kA = 14
};

class Card {
public:
	Card(naipe n, value v) : naipe_{ n }, value_{ v } {};

	naipe naipe_;
	value value_;
};