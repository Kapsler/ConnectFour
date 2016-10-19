#include "AiPlayer.h"
#include "Heuristik.h"
#include <iostream>

AiPlayer::AiPlayer(Ownership self, Ownership enemy)
{
	owner = self;
	this->enemy = enemy;
}

AiPlayer::~AiPlayer()
{
}

bool AiPlayer::MakeMove(sf::RenderWindow* window, Board* board)
{
	int bestMove = FindBestMove(board);

	//Put token in best slot
	board->PutTokenInSlot(bestMove, owner);

	return true;
}

int AiPlayer::evaluate(Board* board) const
{
	int score = 0;

	score += CheckHorizontals(board);
	score += CheckVerticals(board);
	score += CheckDiagonals(board);
	score += CheckAntidiagonals(board);

	return score;
}

int inline AiPlayer::CheckHorizontals(Board* board) const
{
	auto boardArray = board->getArray();
	int score = 0;

	for (int i = 5; i >= 0; --i)
	{
		score += GetHeuristik(boardArray[0][i]->getOwner(), boardArray[1][i]->getOwner(), boardArray[2][i]->getOwner(), boardArray[3][i]->getOwner());
		score += GetHeuristik(boardArray[1][i]->getOwner(), boardArray[2][i]->getOwner(), boardArray[3][i]->getOwner(), boardArray[4][i]->getOwner());
		score += GetHeuristik(boardArray[2][i]->getOwner(), boardArray[3][i]->getOwner(), boardArray[4][i]->getOwner(), boardArray[5][i]->getOwner());
		score += GetHeuristik(boardArray[3][i]->getOwner(), boardArray[4][i]->getOwner(), boardArray[5][i]->getOwner(), boardArray[6][i]->getOwner());
	}
	return score;
}

int inline AiPlayer::CheckVerticals(Board* board) const
{
	auto boardArray = board->getArray();
	int score = 0;

	for (int i = 0; i < 7; ++i)
	{
		score += GetHeuristik(boardArray[i][5]->getOwner(), boardArray[i][4]->getOwner(), boardArray[i][3]->getOwner(), boardArray[i][2]->getOwner());
		score += GetHeuristik(boardArray[i][4]->getOwner(), boardArray[i][3]->getOwner(), boardArray[i][2]->getOwner(), boardArray[i][1]->getOwner());
		score += GetHeuristik(boardArray[i][3]->getOwner(), boardArray[i][2]->getOwner(), boardArray[i][1]->getOwner(), boardArray[i][0]->getOwner());

	}
	return score;
}

int inline AiPlayer::CheckDiagonals(Board* board) const
{
	auto boardArray = board->getArray();
	int score = 0;

	for (int i = 0; i < 4; ++i)
	{
		score += GetHeuristik(boardArray[i][5]->getOwner(), boardArray[i+1][4]->getOwner(), boardArray[i+2][3]->getOwner(), boardArray[i+3][2]->getOwner());
		score += GetHeuristik(boardArray[i][4]->getOwner(), boardArray[i+1][3]->getOwner(), boardArray[i+2][2]->getOwner(), boardArray[i+3][1]->getOwner());
		score += GetHeuristik(boardArray[i][3]->getOwner(), boardArray[i+1][2]->getOwner(), boardArray[i+2][1]->getOwner(), boardArray[i+3][0]->getOwner());
	}
	return score;
}

int inline AiPlayer::CheckAntidiagonals(Board* board) const
{
	auto boardArray = board->getArray();
	int score = 0;

	for (int i = 0; i < 4; ++i)
	{
		score += GetHeuristik(boardArray[i][0]->getOwner(), boardArray[i + 1][1]->getOwner(), boardArray[i + 2][2]->getOwner(), boardArray[i + 3][3]->getOwner());
		score += GetHeuristik(boardArray[i][1]->getOwner(), boardArray[i + 1][2]->getOwner(), boardArray[i + 2][3]->getOwner(), boardArray[i + 3][4]->getOwner());
		score += GetHeuristik(boardArray[i][2]->getOwner(), boardArray[i + 1][3]->getOwner(), boardArray[i + 2][4]->getOwner(), boardArray[i + 3][5]->getOwner());
	}
	return score;
}

int AiPlayer::NegaMax(Board* board, int depth, int alpha, int beta, int color)
{
	bool winning = board->getWin();
	if (depth == 0 || winning)
	{
		//DebugBoard(board);
		int heuristik = evaluate(board);
		//std::cout << "Heuristik:" << heuristik << std::endl << std::endl;
		return color * heuristik;
	}

	std::vector<Board*> nextMoves;

	for (int i = 0; i < 7; ++i)
	{
		if (board->hasEmptyToken(i))
		{
			Board* move = new Board(*board);

			if(color == -1)
			{
				move->PutTokenInSlot(i, owner);
			} else
			{
				move->PutTokenInSlot(i, enemy);
			}
			
			nextMoves.push_back(move);
		}
	}

	int bestValue = -10000000;
	for(int i = 0; i < nextMoves.size(); ++i)
	{
		int score =  -1 * NegaMax(nextMoves.at(i), depth - 1, -beta, -alpha, -color);
		bestValue = std::max(bestValue, score);
		//Alpha Beta Pruning
		alpha = std::max(alpha, score);
		if(alpha >= beta)
		{
			break;
		}
	}

	//std::cout << "Best Child:" << bestValue << std::endl;
	//Clear Moves
	for(auto i : nextMoves)
	{
		delete i;
	}

	return bestValue;
}

int AiPlayer::FindBestMove(Board* board)
{
	std::vector<Board*> nextMoves;

	for (int i = 0; i < 7; ++i)
	{
		if (board->hasEmptyToken(i))
		{
			Board* move = new Board(*board);

			move->PutTokenInSlot(i, owner);

			nextMoves.push_back(move);
		}
	}

	int debugBoardIndex = 0;
	//Evaluate Boards
	int highestValueSlot = nextMoves.at(0)->getLastPlayedSlot();
	int highestValue = NegaMax(nextMoves.at(0), 10, -10000000, 10000000, 1);
	for (int i = 1; i < nextMoves.size(); i++)
	{
		std::cout << "Checking child path: " << i << std::endl;
		int newValue = NegaMax(nextMoves.at(i), 10, -10000000, 10000000, 1);
		//Get highest Board
		if (newValue > highestValue)
		{
			highestValue = newValue;
			highestValueSlot = nextMoves.at(i)->getLastPlayedSlot();
			debugBoardIndex = i;
		}
	}

	std::cout << "Highest Value:" << highestValue << std::endl;
	std::cout << "Highest Slot:" << highestValueSlot << std::endl;
	DebugBoard(nextMoves.at(debugBoardIndex));

	for(auto i : nextMoves)
	{
		delete i;
	}
	nextMoves.clear();

	return highestValueSlot;
}

int inline AiPlayer::GetHeuristik(Ownership first, Ownership second, Ownership third, Ownership fourth) const
{
	int score = 0;

	//XXXX
	if (first == owner && second == owner && third == owner && fourth == owner) score += 10000000;

	//XXX_ || _XXX 
	if ((first == owner && second == owner && third == owner && fourth == NONE) ||
		(first == NONE && second == owner && third == owner && fourth == owner))
		score += 500;
	//XX_X || X_XX
	if ((first == owner && second == owner && third == NONE && fourth == owner) ||
		(first == owner && second == NONE && third == owner && fourth == owner))
		score += 300;

	//XX__ || __XX || X__X || _XX_
	if ((first == owner && second == owner && third == NONE && fourth == NONE) ||
		(first == NONE && second == NONE && third == owner && fourth == owner) ||
		(first == owner && second == NONE && third == NONE && fourth == owner) ||
		(first == NONE && second == owner && third == owner && fourth == NONE))
		score += 150;

	//X___ || ___X || _X__ || __X_
	if ((first == owner && second == NONE && third == NONE && fourth == NONE) ||
		(first == NONE && second == NONE && third == NONE && fourth == owner) ||
		(first == NONE && second == NONE && third == owner && fourth == NONE) ||
		(first == NONE && second == owner && third == NONE && fourth == NONE))
		score += 100;

	//Gegner Konter
	if ((first == enemy && second == enemy && third == enemy && fourth == owner) ||
		(first == enemy && second == enemy && third == owner && fourth == enemy) ||
		(first == enemy && second == owner && third == enemy && fourth == enemy) ||
		(first == owner && second == enemy && third == enemy && fourth == enemy))
		score += 1000;
	//Gegner Konter
	if ((first == owner && second == owner && third == owner && fourth == enemy) ||
		(first == owner && second == owner && third == enemy && fourth == owner) ||
		(first == owner && second == enemy && third == owner && fourth == owner) ||
		(first == enemy && second == owner && third == owner && fourth == owner))
		score -= 1000;

	//Gegner 1er
	if ((first == NONE && second == NONE && third == NONE && fourth == enemy) ||
		(first == NONE && second == NONE && third == enemy && fourth == NONE) ||
		(first == NONE && second == enemy && third == NONE && fourth == NONE) ||
		(first == enemy && second == NONE && third == NONE && fourth == NONE))
		score -= 100;

	//Gegner 2er
	if ((first == enemy && second == enemy && third == NONE && fourth == NONE) ||
		(first == NONE && second == NONE && third == enemy && fourth == enemy) ||
		(first == enemy && second == NONE && third == NONE && fourth == enemy) ||
		(first == NONE && second == enemy && third == enemy && fourth == NONE))
		score -= 150;

	//Gegner 3er
	if ((first == enemy && second == NONE && third == enemy && fourth == enemy) ||
		(first == enemy && second == enemy && third == NONE && fourth == enemy))
		score -= 300;

	if ((first == enemy && second == enemy && third == enemy && fourth == NONE) ||
		(first == NONE && second == enemy && third == enemy && fourth == enemy))
		score -= 500;

	//Gegner 4er
	if (first == enemy && second == enemy && third == enemy && fourth == enemy) score -= 10000000;

	//Old
	//if (ownCount == 4) score += 10000000;
	//if (ownCount == 3 && emptyCount == 1) score += 1000;
	//if (ownCount == 2 && emptyCount == 2) score += 100;
	//if (ownCount == 1 && emptyCount == 3) score += 10;

	////Konter von Gegner 3er
	//if (ownCount == 1 && emptyCount == 0) score += 1500;

	//if (ownCount == 0 && emptyCount == 3) score += -10;
	//if (ownCount == 0 && emptyCount == 2) score += -100;
	//if (ownCount == 0 && emptyCount == 1) score += -1000;
	//if (ownCount == 0 && emptyCount == 0) score += -10000000;

	return score;
}

void AiPlayer::DebugBoard(Board* board)
{
	auto boardarray = board->getArray();

	for(int i = 0; i < 6; ++i)
	{
		for(int j = 0; j < 7; ++j)
		{
			std::cout << boardarray.at(j).at(i)->getOwner();

		}
		std::cout << std::endl;
	}

}
