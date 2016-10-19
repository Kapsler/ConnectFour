#pragma once
#include "Player.h"
#include "GameManager.h"

class AiPlayer : public Player
{
public:
	AiPlayer(Ownership self, Ownership enemy);
	~AiPlayer();

	bool MakeMove(sf::RenderWindow* window, Board* board) override;

private:
	int evaluate(Board* board) const;
	int inline CheckHorizontals(Board* board) const;
	int inline CheckVerticals(Board* board) const;
	int inline CheckDiagonals(Board* board) const;
	int inline CheckAntidiagonals(Board* board) const;
	int NegaMax(Board* board, int depth, int alpha, int beta, int color, int &bestslot);
	int FindBestMove(Board* board);
	int inline GetHeuristik(Ownership first, Ownership second, Ownership third, Ownership fourth) const;

	void DebugBoard(Board* board);

};
