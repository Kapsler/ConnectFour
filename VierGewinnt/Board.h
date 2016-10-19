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
	const bool getWin() const;
	Ownership getOwnerOfToken(sf::Vector2<int> pos);
	bool hasEmptyToken(int slotNumber);
	int getLastPlayedSlot();
	sf::Vector2<int> getLastPlayedToken();
	const std::vector<std::vector<Token*>> getArray() const;
	bool removeLastToken(int slot);

private:
	std::vector<std::vector<Token*>> board;

	std::vector<sf::Vector2<int>> lastPlayedToken;
	bool win;
};
