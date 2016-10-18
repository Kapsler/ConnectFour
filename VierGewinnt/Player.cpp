#include "Player.h"

Player::Player()
{
	owner = NONE;
	enemy = NONE;
}

Player::~Player()
{
}

Ownership Player::getIdentifier()
{
	return owner;
}
