#include "AiPlayer.h"

AiPlayer::AiPlayer()
{
	owner = PLAYER2;
}

AiPlayer::~AiPlayer()
{
}

bool AiPlayer::MakeMove(sf::RenderWindow* window, Board* board)
{
	for(int i = 0; i < 7; i++)
	{
		if(board->hasEmptyToken(i))
		{
			Board* move = new Board(*board);

			move->PutTokenInSlot(i, owner);

			nextMoves.push_back(move);
			break;
		}
	}

	//Evaluate Boards
	int highestValueSlot = nextMoves.at(0)->getLastPlayedSlot();
	int highestValue = evaluate(nextMoves.at(0));
	for(int i = 1; i < nextMoves.size(); i++)
	{
		int newValue = evaluate(nextMoves.at(i));
		//Get highest Board
		if(newValue > highestValue)
		{
			highestValue = newValue;
			highestValueSlot = nextMoves.at(i)->getLastPlayedSlot();
		}
	}

	//Put token in best slot
	board->PutTokenInSlot(highestValueSlot, owner);

	ClearNextMoves();

	return true;
}

int AiPlayer::evaluate(Board* board)
{
	return 1;
}



void AiPlayer::ClearNextMoves()
{
	for(auto i : nextMoves)
	{
		delete i;
	}

	nextMoves.clear();
}

int AiPlayer::CheckHorizontals(Board* board)
{
	auto boardArray = board->getArray();
	int selfCounter = 0;
	int opponentCounter = 0;
	for (int i = 5; i >= 0; --i)
	{
		if(	boardArray[0][0]->getOwner() == owner &&
			boardArray[0][1]->getOwner() == owner &&
			boardArray[0][2]->getOwner() == owner &&
			boardArray[0][3]->getOwner() == owner)
		{
			
		}



	}
}

int AiPlayer::CheckVerticals(Board* board)
{
	return 0;
}

int AiPlayer::CheckDiagonals(Board* board)
{
	return 0;
}

int AiPlayer::CheckAntidiagonals(Board* board)
{
	return 0;
}
