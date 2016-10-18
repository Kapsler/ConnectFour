#pragma once
#include <SFML/Graphics.hpp>
#include "OwnershipEnum.h"
#include "Board.h"

class Player
{
public:
	Player();
	virtual ~Player();

	virtual bool MakeMove(sf::RenderWindow* window, Board* board) = 0;
	virtual Ownership getIdentifier();
	Ownership owner, enemy;

private:
};
