#pragma once
#include <SFML/Graphics.hpp>
#include "OwnershipEnum.h"

class Token
{
public:
	Token(sf::Vector2<float> position);
	Token(const Token &other);
	~Token();

	void Render(sf::RenderWindow* window);
	void setSelected(bool state);
	bool isFilled() const;
	void SetOwnership(Ownership player);
	void setRow(int row);
	void SetColumn(int column);
	sf::Vector2<int> getPosition() const;
	Ownership getOwner() const;
	const sf::CircleShape getShape() const;
	const sf::RectangleShape getBackground() const;
	void setFilled(bool newState);

private:
	sf::CircleShape* shape;
	sf::RectangleShape* background;
	
	bool filled;
	Ownership owner;
	sf::Vector2<int> position;
};