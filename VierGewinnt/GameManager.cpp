#include "GameManager.h"

GameManager::GameManager(int columns, int rows)
{
	board = new Board(columns, rows);

	selectedSlot = 0;
	board->SelectSlot(selectedSlot, selectedSlot);

	PlayerTurn = PLAYER1;
}

GameManager::~GameManager()
{

}

void GameManager::PutTokenInSlot()
{
	board->PutTokenInSlot(selectedSlot, WhoseTurn());
	ToggleTurn();
}

void GameManager::SelectSlotRight()
{
	selectedSlot = board->SelectSlot(selectedSlot, selectedSlot + 1);
}

void GameManager::SelectSlotLeft()
{
	selectedSlot = board->SelectSlot(selectedSlot, selectedSlot - 1);
}

bool GameManager::Run()
{
	if(checkWin())
	{
		return false;
	}

	return true;
}

void GameManager::Render(sf::RenderWindow* window)
{
	//Draw Board
	board->Render(window);
}

void GameManager::ToggleTurn()
{
	if (PlayerTurn == PLAYER1)
	{
		PlayerTurn = PLAYER2;
	}
	else
	{
		PlayerTurn = PLAYER1;
	}
}

bool GameManager::checkWin()
{
	return board->getWin();
}

Ownership GameManager::WhoseTurn()
{
	return PlayerTurn;
}
