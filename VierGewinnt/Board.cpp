#include "Board.h"
#include <iostream>

Board::Board(int columns, int rows)
{
	sf::Vector2<float> position(0.0f, 0.0f);
	std::vector<Token*> slot;

	for(auto i = 0; i < columns; ++i)
	{
		for(auto j = 0; j < rows; ++j)
		{
			Token* token = new Token(position);
			token->setRow(j);
			token->SetColumn(i);
			slot.push_back(token);
			position.y += 100.0f;
		}
		position.y = 0.0f;
		position.x += 100.0f;
		board.push_back(slot);
		slot.clear();
	}
}

Board::~Board()
{
	for(auto i : board)
	{
		for (auto j : i)
		{
			delete j;
		}
	}
}

void Board::Render(sf::RenderWindow* window)
{
	for(auto i : board)
	{
		for(auto j : i)
		{
			j->Render(window);
		}
	}
}

int Board::SelectSlot(int oldSlot, int newSlot)
{
	if (newSlot >= 0 && newSlot < board.size())
	{
		for (auto i : board[oldSlot])
		{
			i->setSelected(false);
		}

		for(auto i : board[newSlot])
		{
			i->setSelected(true);
		}

		return newSlot;
	} else
	{
		return oldSlot;
	}
}

bool Board::FourInARow()
{
	return false;
}

bool Board::hasEmptyToken(int slotNumber)
{
	for (auto i = board[slotNumber].rbegin(); i != board[slotNumber].rend(); ++i)
	{
		if (!((*i)->isFilled()))
		{
			return true;
		}
	}

	return false;
}

void Board::PutTokenInSlot(int slot, Ownership owner)
{
	//Find Last empty Token and place chip
	for (auto i = board[slot].rbegin(); i != board[slot].rend(); ++i)
	{
		if (!((*i)->isFilled()))
		{
			(*i)->SetOwnership(owner);
			lastPlayedToken = (*i)->getPosition();
			break;
		}
	}

	std::cout << lastPlayedToken.x << " " << lastPlayedToken.y << std::endl;
}

