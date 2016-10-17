#include "HumanPlayer.h"
#include <iostream>

HumanPlayer::HumanPlayer()
{
	owner = PLAYER1;
	selectedSlot = 0;
}

HumanPlayer::~HumanPlayer()
{
}

bool HumanPlayer::MakeMove(sf::RenderWindow* window, Board* board)
{
	sf::Event event;

	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			//Get Input
			if (event.key.code == sf::Keyboard::Key::Right)
			{
				SelectSlotRight(board);
			}
			if (event.key.code == sf::Keyboard::Key::Left)
			{
				SelectSlotLeft(board);
			}
			if (event.key.code == sf::Keyboard::Key::Space)
			{
				return PutTokenInSlot(board);
			}
			if (event.key.code == sf::Keyboard::Key::Escape)
			{
				window->close();
			}
		}
	}

	return false;
}

void HumanPlayer::SelectSlotRight(Board* board)
{
	selectedSlot = board->SelectSlot(selectedSlot, selectedSlot + 1);
}

void HumanPlayer::SelectSlotLeft(Board* board)
{
	selectedSlot = board->SelectSlot(selectedSlot, selectedSlot - 1);
}

bool HumanPlayer::PutTokenInSlot(Board* board)
{
	return board->PutTokenInSlot(selectedSlot, owner);

}
