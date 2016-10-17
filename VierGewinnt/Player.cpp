#include "Player.h"

Player::Player()
{
	owner = NONE;
}

Player::~Player()
{
}

Ownership Player::getIdentifier()
{
	return owner;
}
