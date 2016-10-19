#include "Heuristik.h"
#include <iostream>

Heuristik::Heuristik(Ownership first, Ownership second, Ownership third, Ownership fourth, Ownership self, Ownership enemy)
{
	tokens = new Ownership[4];

	tokens[0] = first;
	tokens[1] = second;
	tokens[2] = third;
	tokens[3] = fourth;
	target = self;
	this->enemy = enemy;
}

Heuristik::~Heuristik()
{
	delete[] tokens;
}

int Heuristik::getHeuristik()
{
	int score = 0;

	//XXXX
	if (tokens[0] == target && tokens[1] == target && tokens[2] == target && tokens[3] == target) score += 10000000;

	//XXX_ || _XXX 
	if ((tokens[0] == target && tokens[1] == target && tokens[2] == target && tokens[3] == NONE) ||
		(tokens[0] == NONE && tokens[1] == target && tokens[2] == target && tokens[3] == target))
			score += 1500;
	//XX_X || X_XX
	if ((tokens[0] == target && tokens[1] == target && tokens[2] == NONE && tokens[3] == target) ||
		(tokens[0] == target && tokens[1] == NONE && tokens[2] == target && tokens[3] == target))
			score += 1000;

	//XX__ || __XX || X__X || _XX_
	if ((tokens[0] == target && tokens[1] == target && tokens[2] == NONE && tokens[3] == NONE) ||
		(tokens[0] == NONE && tokens[1] == NONE && tokens[2] == target && tokens[3] == target) ||
		(tokens[0] == target && tokens[1] == NONE && tokens[2] == NONE && tokens[3] == target) ||
		(tokens[0] == NONE && tokens[1] == target && tokens[2] == target && tokens[3] == NONE))
			score += 100;

	//Gegner Konter
	if ((tokens[0] == enemy && tokens[1] == enemy && tokens[2] == enemy && tokens[3] == target) ||
		(tokens[0] == enemy && tokens[1] == enemy && tokens[2] == target && tokens[3] == enemy) ||
		(tokens[0] == enemy && tokens[1] == target && tokens[2] == enemy && tokens[3] == enemy) ||
		(tokens[0] == target && tokens[1] == enemy && tokens[2] == enemy && tokens[3] == enemy))
		score += 2000;
	

	//Gegner 2er
	if ((tokens[0] == enemy && tokens[1] == enemy && tokens[2] == NONE && tokens[3] == NONE) ||
		(tokens[0] == NONE && tokens[1] == NONE && tokens[2] == enemy && tokens[3] == enemy) ||
		(tokens[0] == enemy && tokens[1] == NONE && tokens[2] == NONE && tokens[3] == enemy) ||
		(tokens[0] == NONE && tokens[1] == enemy && tokens[2] == enemy && tokens[3] == NONE))
		score -= 100;

	//Gegner 3er
	if ((tokens[0] == enemy && tokens[1] == enemy && tokens[2] == enemy && tokens[3] == NONE) ||
		(tokens[0] == NONE && tokens[1] == enemy && tokens[2] == enemy && tokens[3] == NONE))
		score -= 1500;

	if ((tokens[0] == enemy && tokens[1] == NONE && tokens[2] == enemy && tokens[3] == enemy) ||
		(tokens[0] == enemy && tokens[1] == enemy && tokens[2] == NONE && tokens[3] == enemy))
		score -= 1000;

	//Gegner 4er
	if (tokens[0] == enemy && tokens[1] == enemy && tokens[2] == enemy && tokens[3] == enemy) score -= 10000000;




	//if (ownCount == 4) score += 10000000;
	//if (ownCount == 3 && emptyCount == 1) score += 1000;
	//if (ownCount == 2 && emptyCount == 2) score += 100;
	//if (ownCount == 1 && emptyCount == 3) score += 10;

	////Konter von Gegner 3er
	//if (ownCount == 1 && emptyCount == 0) score += 1500;

	//if (ownCount == 0 && emptyCount == 3) score += -10;
	//if (ownCount == 0 && emptyCount == 2) score += -100;
	//if (ownCount == 0 && emptyCount == 1) score += -1000;
	//if (ownCount == 0 && emptyCount == 0) score += -10000000;

	return score;
}
