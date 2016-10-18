#include "AiPlayer.h"
#include "Heuristik.h"
#include <iostream>

AiPlayer::AiPlayer()
{
	owner = PLAYER2;
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

int AiPlayer::evaluate(Board* board)
{
	int score = 0;

	score += CheckHorizontals(board);
	score += CheckVerticals(board);
	score += CheckDiagonals(board);
	score += CheckAntidiagonals(board);

	return score;
}

int AiPlayer::CheckHorizontals(Board* board)
{
	auto boardArray = board->getArray();
	int score = 0;

	for (int i = 5; i >= 0; --i)
	{
		Heuristik temp1(boardArray[0][i]->getOwner(), boardArray[1][i]->getOwner(), boardArray[2][i]->getOwner(), boardArray[3][i]->getOwner(), owner);
		Heuristik temp2(boardArray[1][i]->getOwner(), boardArray[2][i]->getOwner(), boardArray[3][i]->getOwner(), boardArray[4][i]->getOwner(), owner);
		Heuristik temp3(boardArray[2][i]->getOwner(), boardArray[3][i]->getOwner(), boardArray[4][i]->getOwner(), boardArray[5][i]->getOwner(), owner);
		Heuristik temp4(boardArray[3][i]->getOwner(), boardArray[4][i]->getOwner(), boardArray[5][i]->getOwner(), boardArray[6][i]->getOwner(), owner);

		score += temp1.getHeuristik() + temp2.getHeuristik() + temp3.getHeuristik() + temp4.getHeuristik();
	
	}
	return score;
}

int AiPlayer::CheckVerticals(Board* board)
{
	auto boardArray = board->getArray();
	int score = 0;

	for (int i = 0; i < 7; ++i)
	{
		Heuristik temp1(boardArray[i][5]->getOwner(), boardArray[i][4]->getOwner(), boardArray[i][3]->getOwner(), boardArray[i][2]->getOwner(), owner);
		Heuristik temp2(boardArray[i][4]->getOwner(), boardArray[i][3]->getOwner(), boardArray[i][2]->getOwner(), boardArray[i][1]->getOwner(), owner);
		Heuristik temp3(boardArray[i][3]->getOwner(), boardArray[i][2]->getOwner(), boardArray[i][1]->getOwner(), boardArray[i][0]->getOwner(), owner);
	
		score += temp1.getHeuristik() + temp2.getHeuristik() + temp3.getHeuristik();

	}
	return score;
}

int AiPlayer::CheckDiagonals(Board* board)
{
	auto boardArray = board->getArray();
	int score = 0;

	for (int i = 0; i < 4; ++i)
	{
		Heuristik temp1(boardArray[i][5]->getOwner(), boardArray[i+1][4]->getOwner(), boardArray[i+2][3]->getOwner(), boardArray[i+3][2]->getOwner(), owner);
		Heuristik temp2(boardArray[i][4]->getOwner(), boardArray[i+1][3]->getOwner(), boardArray[i+2][2]->getOwner(), boardArray[i+3][1]->getOwner(), owner);
		Heuristik temp3(boardArray[i][3]->getOwner(), boardArray[i+1][2]->getOwner(), boardArray[i+2][1]->getOwner(), boardArray[i+3][0]->getOwner(), owner);

		score += temp1.getHeuristik() + temp2.getHeuristik() + temp3.getHeuristik();
	}
	return score;
}

int AiPlayer::CheckAntidiagonals(Board* board)
{
	auto boardArray = board->getArray();
	int score = 0;

	for (int i = 0; i < 4; ++i)
	{
		Heuristik temp1(boardArray[i][0]->getOwner(), boardArray[i + 1][1]->getOwner(), boardArray[i + 2][2]->getOwner(), boardArray[i + 3][3]->getOwner(), owner);
		Heuristik temp2(boardArray[i][1]->getOwner(), boardArray[i + 1][2]->getOwner(), boardArray[i + 2][3]->getOwner(), boardArray[i + 3][4]->getOwner(), owner);
		Heuristik temp3(boardArray[i][2]->getOwner(), boardArray[i + 1][3]->getOwner(), boardArray[i + 2][4]->getOwner(), boardArray[i + 3][5]->getOwner(), owner);

		score += temp1.getHeuristik() + temp2.getHeuristik() + temp3.getHeuristik();
	}
	return score;
}

int AiPlayer::NegaMax(Board* board, int depth, int alpha, int beta, int color)
{
	bool winning = board->getWin();
	if (depth == 0 || board->BoardIsFull() || winning)
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
				move->PutTokenInSlot(i, PLAYER1);
			}
			
			nextMoves.push_back(move);
		}
	}

	int bestValue = -10000000;
	for(int i = 0; i < nextMoves.size(); ++i)
	{
		int score = -1 * NegaMax(nextMoves.at(i), depth - 1, -beta, -alpha, -color);
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
	int highestValue = NegaMax(nextMoves.at(0), 7, -1000000, 1000000, 1);
	for (int i = 1; i < nextMoves.size(); i++)
	{
		int newValue = NegaMax(nextMoves.at(i), 7, -1000000, 1000000, 1);
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