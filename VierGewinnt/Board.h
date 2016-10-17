#pragma once
#include <vector>
#include "Token.h"

class Board
{
	
public:
	Board(int columns, int rows);
	Board(const Board &other);
	~Board();

	void Render(sf::RenderWindow* window);
	bool PutTokenInSlot(int slot, Ownership player);
	int SelectSlot(int oldSlot, int newSlot);
	bool FourInARow(sf::Vector2<int> token, Ownership player);
	bool BoardIsFull();
	bool getWin();
	Ownership getOwnerOfToken(sf::Vector2<int> pos);
	bool hasEmptyToken(int slotNumber);
	int getLastPlayedSlot();
	std::vector<std::vector<Token*>> getArray();

private:
	std::vector<std::vector<Token*>> board;

	sf::Vector2<int> lastPlayedToken;
	bool win;
};
