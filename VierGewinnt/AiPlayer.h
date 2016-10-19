#pragma once
#include "Player.h"
#include "GameManager.h"
#include "TimerClass.h"
#include "AiMode.h"

class AiPlayer : public Player
{
public:
	AiPlayer(Ownership self, Ownership enemy, int depth, AiMode newmode);
	~AiPlayer();

	bool MakeMove(sf::RenderWindow* window, Board* board) override;

private:
	int evaluate(Board* board) const;
	int inline CheckHorizontals(const std::vector<std::vector<Token*>>* boardarray) const;
	int inline CheckVerticals(const std::vector<std::vector<Token*>>* boardarray) const;
	int inline CheckDiagonals(const std::vector<std::vector<Token*>>* boardarray) const;
	int inline CheckAntidiagonals(const std::vector<std::vector<Token*>>* boardarray) const;
	int NegaMax(Board* board, int depth, int alpha, int beta, int color, int &bestslot);
	int NegaMax(Board* board, int depth, int color, int &bestslot);
	int NegaMax(Board* board, int color, int &bestslot);
	int FindBestMove(Board* board);
	int inline GetHeuristik(Ownership first, Ownership second, Ownership third, Ownership fourth) const;

	static void DebugBoard(Board* board);
	int playdepth;
	TimerClass* timer;
	AiMode mode;
};
