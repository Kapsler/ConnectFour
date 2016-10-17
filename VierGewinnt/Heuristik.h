#pragma once
#include "OwnershipEnum.h"
#include <vector>

class Heuristik
{
public:	
	Heuristik(Ownership first, Ownership second, Ownership third, Ownership fourth, Ownership self);
	~Heuristik();

	int getHeuristik();

private:
	void DebugOutput();

	std::vector<Ownership> tokens;
	Ownership target;

};
