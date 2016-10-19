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
	Board* root = new Board(*board);

	int bestMove = FindBestMove(root);

	delete root;
	//Put token in best slot
	board->PutTokenInSlot(bestMove, owner);

	return true;
}

int AiPlayer::evaluate(Board* board) const
{
	int score = 0;

	const std::vector<std::vector<Token*>>* boardArray = board->GetArrayPtr();

	score += CheckHorizontals(boardArray);
	score += CheckVerticals(boardArray);
	score += CheckDiagonals(boardArray);
	score += CheckAntidiagonals(boardArray);

	return score;
}

int inline AiPlayer::CheckHorizontals(const std::vector<std::vector<Token*>>* boardArray) const
{
	int score = 0;

	for (int i = 5; i >= 0; --i)
	{
		score += GetHeuristik((*boardArray)[0][i]->getOwner(), (*boardArray)[1][i]->getOwner(), (*boardArray)[2][i]->getOwner(), (*boardArray)[3][i]->getOwner());
		score += GetHeuristik((*boardArray)[1][i]->getOwner(), (*boardArray)[2][i]->getOwner(), (*boardArray)[3][i]->getOwner(), (*boardArray)[4][i]->getOwner());
		score += GetHeuristik((*boardArray)[2][i]->getOwner(), (*boardArray)[3][i]->getOwner(), (*boardArray)[4][i]->getOwner(), (*boardArray)[5][i]->getOwner());
		score += GetHeuristik((*boardArray)[3][i]->getOwner(), (*boardArray)[4][i]->getOwner(), (*boardArray)[5][i]->getOwner(), (*boardArray)[6][i]->getOwner());
	}
	return score;
}

int inline AiPlayer::CheckVerticals(const std::vector<std::vector<Token*>>* boardArray) const
{
	int score = 0;

	for (int i = 0; i < 7; ++i)
	{
		score += GetHeuristik((*boardArray)[i][5]->getOwner(), (*boardArray)[i][4]->getOwner(), (*boardArray)[i][3]->getOwner(), (*boardArray)[i][2]->getOwner());
		score += GetHeuristik((*boardArray)[i][4]->getOwner(), (*boardArray)[i][3]->getOwner(), (*boardArray)[i][2]->getOwner(), (*boardArray)[i][1]->getOwner());
		score += GetHeuristik((*boardArray)[i][3]->getOwner(), (*boardArray)[i][2]->getOwner(), (*boardArray)[i][1]->getOwner(), (*boardArray)[i][0]->getOwner());

	}
	return score;
}

int inline AiPlayer::CheckDiagonals(const std::vector<std::vector<Token*>>* boardArray) const
{
	int score = 0;

	for (int i = 0; i < 4; ++i)
	{
		score += GetHeuristik((*boardArray)[i][5]->getOwner(), (*boardArray)[i+1][4]->getOwner(), (*boardArray)[i+2][3]->getOwner(), (*boardArray)[i+3][2]->getOwner());
		score += GetHeuristik((*boardArray)[i][4]->getOwner(), (*boardArray)[i+1][3]->getOwner(), (*boardArray)[i+2][2]->getOwner(), (*boardArray)[i+3][1]->getOwner());
		score += GetHeuristik((*boardArray)[i][3]->getOwner(), (*boardArray)[i+1][2]->getOwner(), (*boardArray)[i+2][1]->getOwner(), (*boardArray)[i+3][0]->getOwner());
	}
	return score;
}

int inline AiPlayer::CheckAntidiagonals(const std::vector<std::vector<Token*>>* boardArray) const
{
	int score = 0;

	for (int i = 0; i < 4; ++i)
	{
		score += GetHeuristik((*boardArray)[i][0]->getOwner(), (*boardArray)[i + 1][1]->getOwner(), (*boardArray)[i + 2][2]->getOwner(), (*boardArray)[i + 3][3]->getOwner());
		score += GetHeuristik((*boardArray)[i][1]->getOwner(), (*boardArray)[i + 1][2]->getOwner(), (*boardArray)[i + 2][3]->getOwner(), (*boardArray)[i + 3][4]->getOwner());
		score += GetHeuristik((*boardArray)[i][2]->getOwner(), (*boardArray)[i + 1][3]->getOwner(), (*boardArray)[i + 2][4]->getOwner(), (*boardArray)[i + 3][5]->getOwner());
	}
	return score;
}

int AiPlayer::NegaMax(Board* board, int depth, int alpha, int beta, int color, int &bestslot)
{
	bool winning = board->getWin();
	if (depth == 0)
	{
		//DebugBoard(board);
		int heuristik = evaluate(board);
		//std::cout << "Heuristik:" << heuristik << std::endl << std::endl;
		return color * heuristik;
	}
	if (winning)
	{
		int heuristik = evaluate(board);
		return color * depth * heuristik;
	}

	int bestValue = INT_MIN + 1;
	for (int i = 0; i < 7; ++i)
	{
		if (board->hasEmptyToken(i))
		{
			if(color == 1)
			{
				board->PutTokenInSlot(i, owner);
			} else
			{
				board->PutTokenInSlot(i, enemy);
			}
			int temp = 0;
			int score = -1 * NegaMax(board, depth - 1, -beta, -alpha, -color, temp);
			if (score > bestValue)
			{
				bestslot = i;
				bestValue = score;
			}

			board->removeLastToken(i);

			//Alpha Beta Pruning
			alpha = std::max(alpha, score);
			if (alpha >= beta)
			{
				break;
			}
		}
	}

	return bestValue;
}

int AiPlayer::FindBestMove(Board* board)
{
	
	//Evaluate Boards
	int highestValueSlot = 0;
	int highestValue = NegaMax(board, 10, INT_MIN+1, INT_MAX, 1, highestValueSlot);

	std::cout << "Highest Value:" << highestValue << std::endl;
	std::cout << "Highest Slot:" << highestValueSlot << std::endl;

	return highestValueSlot;
}

int inline AiPlayer::GetHeuristik(Ownership first, Ownership second, Ownership third, Ownership fourth) const
{
	int score = 0;

	//XXXX
	if (first == owner && second == owner && third == owner && fourth == owner)	score += 100;

	//XXX_ || _XXX 
	if ((first == owner && second == owner && third == owner && fourth == NONE) ||
		(first == NONE && second == owner && third == owner && fourth == owner))
		score += 10;
	//XX_X || X_XX
	if ((first == owner && second == owner && third == NONE && fourth == owner) ||
		(first == owner && second == NONE && third == owner && fourth == owner))
		score += 10;

	//XX__ || __XX || X__X || _XX_
	if ((first == owner && second == owner && third == NONE && fourth == NONE) ||
		(first == NONE && second == NONE && third == owner && fourth == owner) ||
		(first == owner && second == NONE && third == NONE && fourth == owner) ||
		(first == owner && second == NONE && third == owner && fourth == NONE) ||
		(first == NONE && second == owner && third == NONE && fourth == owner) ||
		(first == NONE && second == owner && third == owner && fourth == NONE))
		score += 1;

	//X___ || ___X || _X__ || __X_
	if ((first == owner && second == NONE && third == NONE && fourth == NONE) ||
		(first == NONE && second == NONE && third == NONE && fourth == owner) ||
		(first == NONE && second == NONE && third == owner && fourth == NONE) ||
		(first == NONE && second == owner && third == NONE && fourth == NONE))
		score += 0;

	////Gegner Konter
	//if ((first == enemy && second == enemy && third == enemy && fourth == owner) ||
	//	(first == enemy && second == enemy && third == owner && fourth == enemy) ||
	//	(first == enemy && second == owner && third == enemy && fourth == enemy) ||
	//	(first == owner && second == enemy && third == enemy && fourth == enemy))
	//	score += 1000;
	////Gegner Konter
	//if ((first == owner && second == owner && third == owner && fourth == enemy) ||
	//	(first == owner && second == owner && third == enemy && fourth == owner) ||
	//	(first == owner && second == enemy && third == owner && fourth == owner) ||
	//	(first == enemy && second == owner && third == owner && fourth == owner))
	//	score -= 1000;

	//Gegner 1er
	if ((first == NONE && second == NONE && third == NONE && fourth == enemy) ||
		(first == NONE && second == NONE && third == enemy && fourth == NONE) ||
		(first == NONE && second == enemy && third == NONE && fourth == NONE) ||
		(first == enemy && second == NONE && third == NONE && fourth == NONE))
		score -= 0;

	//Gegner 2er
	if ((first == enemy && second == enemy && third == NONE && fourth == NONE) ||
		(first == NONE && second == NONE && third == enemy && fourth == enemy) ||
		(first == enemy && second == NONE && third == NONE && fourth == enemy) ||
		(first == enemy && second == NONE && third == enemy && fourth == NONE) ||
		(first == NONE && second == enemy && third == NONE && fourth == enemy) ||
		(first == NONE && second == enemy && third == enemy && fourth == NONE))
		score -= 1;

	//Gegner 3er
	if ((first == enemy && second == NONE && third == enemy && fourth == enemy) ||
		(first == enemy && second == enemy && third == NONE && fourth == enemy))
		score -= 10;

	if ((first == enemy && second == enemy && third == enemy && fourth == NONE) ||
		(first == NONE && second == enemy && third == enemy && fourth == enemy))
		score -= 10;

	//Gegner 4er
	if (first == enemy && second == enemy && third == enemy && fourth == enemy) score -= 100;

	return score;
}

void AiPlayer::DebugBoard(Board* board)
{
	auto boardArray = board->GetArrayPtr();

	for(int i = 0; i < 6; ++i)
	{
		for(int j = 0; j < 7; ++j)
		{
			std::cout << boardArray->at(j).at(i)->getOwner();

		}
		std::cout << std::endl;
	}

}
