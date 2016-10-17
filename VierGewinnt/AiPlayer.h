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
	std::vector<Board*> nextMoves;
	void ClearNextMoves();
	int CheckHorizontals(Board* board);
	int CheckVerticals(Board* board);
	int CheckDiagonals(Board* board);
	int CheckAntidiagonals(Board* board);

};
