#include "GameManager.h"
#include <iostream>

GameManager::GameManager(int columns, int rows, std::vector<Player*> players)
{
	board = new Board(columns, rows);

	this->players = players;

	turns = 0;
	currentPlayerId = turns;
	currentPlayer = players.at(currentPlayerId);
}

GameManager::~GameManager()
{

}

bool GameManager::isMovePossible(int slot)
{
	return board->hasEmptyToken(slot);
}

bool GameManager::Run(sf::RenderWindow* window)
{
	currentPlayerId = turns % 2;
	currentPlayer = players.at(currentPlayerId);

	if(checkWin())
	{
		return false;
	}

	if(currentPlayer->MakeMove(window, board))
	{
		ToggleTurn();
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
	turns++;
	std::cout << turns << std::endl;
}

bool GameManager::checkWin()
{
	return board->getWin();
}

Ownership GameManager::WhoseTurn()
{
	return currentPlayer->getIdentifier();
}

Board* GameManager::getCurrentBoard()
{
	return board;
}
