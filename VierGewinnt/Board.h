#pragma once
#include <vector>
#include "Token.h"

class Board
{
	
public:
	Board(int columns, int rows);
	~Board();

	void Render(sf::RenderWindow* window);
	void PutTokenInSlot(int slot, Ownership owner);
	int SelectSlot(int oldSlot, int newSlot);
	bool FourInARow();

private:
	std::vector<std::vector<Token*>> board;
	bool hasEmptyToken(int slotNumber);

	sf::Vector2<int> lastPlayedToken;
};
