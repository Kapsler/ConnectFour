#pragma once
#include <SFML/Graphics.hpp>
#include "OwnershipEnum.h"

class Token
{
public:
	Token(sf::Vector2<float> position);
	~Token();

	void Render(sf::RenderWindow* window);
	void setSelected(bool state);
	bool isFilled();
	void SetOwnership(Ownership player);
	void setRow(int row);
	void SetColumn(int column);
	sf::Vector2<int> getPosition();

private:
	sf::CircleShape* shape;
	sf::RectangleShape* background;
	
	bool filled;
	Ownership owner;
	sf::Vector2<int> position;
};