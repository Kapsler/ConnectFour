#pragma once
#include "OwnershipEnum.h"
#include <vector>

class Heuristik
{
public:	
	Heuristik(Ownership first, Ownership second, Ownership third, Ownership fourth, Ownership self, Ownership enemy);
	~Heuristik();

	int getHeuristik();

private:

	Ownership* tokens;
	Ownership target;
	Ownership enemy;

};
