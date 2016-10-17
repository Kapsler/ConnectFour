#pragma once
#include "Board.h"
#include "Player.h"

class GameManager
{
public:
	GameManager(int columns, int rows, std::vector<Player*> players);
	~GameManager();

	bool isMovePossible(int slot);
	Ownership WhoseTurn();
	Board* getCurrentBoard();

	bool Run(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
private:
	void ToggleTurn();
	bool checkWin();

	int selectedSlot;
	Board* board;
	std::vector<Player*> players;
	Player* currentPlayer;
	int turns, currentPlayerId;
};
