#include "Token.h"

Token::Token(sf::Vector2<float> pos)
{
	background = new sf::RectangleShape();
	sf::Vector2<float> rectSize(100.0f, 100.0f);
	background->setSize(rectSize);
	background->setFillColor(sf::Color::Blue);
	background->setPosition(pos);

	shape = new sf::CircleShape(45.0f);
	shape->setFillColor(sf::Color::White);
	pos.x += 50 - shape->getGlobalBounds().height / 2;
	pos.y += 50 - shape->getGlobalBounds().height / 2;
	shape->setPosition(pos);
	filled = false;
	owner = NONE;
}

Token::~Token()
{
	delete shape;
	delete background;
}

void Token::Render(sf::RenderWindow* window)
{
	window->draw(*background);
	window->draw(*shape);
}

void Token::setSelected(bool state)
{
	if (state)
	{
		background->setFillColor(sf::Color::Cyan);
	} else
	{
		background->setFillColor(sf::Color::Blue);
	}

}

bool Token::isFilled()
{
	return filled;
}

void Token::SetOwnership(Ownership player)
{
	owner = player;
	filled = true;
	switch (player)
	{
	case NONE:
		shape->setFillColor(sf::Color::White);
		break;
	case PLAYER1:
		shape->setFillColor(sf::Color::Yellow);
		break;
	case PLAYER2:
		shape->setFillColor(sf::Color::Red);
		break;
	default:
		break;
	}
}

void Token::setRow(int row)
{
	position.y = row;
}

void Token::SetColumn(int column)
{
	position.x = column;
}

sf::Vector2<int> Token::getPosition()
{
	return position;
}

Ownership Token::getOwner()
{
	return owner;
}
