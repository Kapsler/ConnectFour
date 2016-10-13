#pragma once
#include "Board.h"

class GameManager
{
public:
	GameManager(int columns, int rows);
	~GameManager();

	void SelectSlotRight();
	void SelectSlotLeft();
	void PutTokenInSlot();
	Ownership WhoseTurn();

	bool Run();
	void Render(sf::RenderWindow* window);
private:
	void ToggleTurn();
	bool checkWin();

	int selectedSlot;
	Board* board;
	Ownership PlayerTurn;
};
