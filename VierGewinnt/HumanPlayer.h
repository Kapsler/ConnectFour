#pragma once
#include "Player.h"
#include "GameManager.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer();
	~HumanPlayer();

	virtual bool MakeMove(sf::RenderWindow* window, Board* board) override;
private:
	void SelectSlotRight(Board* board);
	void SelectSlotLeft(Board* board);
	bool PutTokenInSlot(Board* board);
	int selectedSlot;
};
