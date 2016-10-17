#pragma once
#include "Player.h"
#include "GameManager.h"

class AiPlayer : public Player
{
public:
	AiPlayer();
	~AiPlayer();

	bool MakeMove(sf::RenderWindow* window, Board* board);

private:
	int evaluate(Board* board);
	int CheckHorizontals(Board* board);
	int CheckVerticals(Board* board);
	int CheckDiagonals(Board* board);
	int CheckAntidiagonals(Board* board);
	int NegaMax(Board* board, int depth, int color);
	int FindBestMove(Board* board);

};
