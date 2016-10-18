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

Token::Token(const Token& other)
{
	shape = nullptr;
	background = nullptr;
	filled = other.isFilled();
	owner = other.getOwner();
	position = other.getPosition();
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

bool Token::isFilled() const
{
	return filled;
}

void Token::SetOwnership(Ownership player)
{
	owner = player;
	switch (player)
	{
	case NONE:
		if(shape)
		{
			shape->setFillColor(sf::Color::White);
		}
		break;
	case PLAYER1:
		if (shape)
		{
		shape->setFillColor(sf::Color::Yellow);
		}
		filled = true;
		break;
	case PLAYER2:
		if (shape)
		{
		shape->setFillColor(sf::Color::Red);
		}
		filled = true;
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

sf::Vector2<int> Token::getPosition() const
{
	return position;
}

Ownership Token::getOwner() const
{
	return owner;
}

const sf::CircleShape Token::getShape() const
{
	return *shape;
}

const sf::RectangleShape Token::getBackground() const
{
	return *background;
}

void Token::setFilled(bool newState)
{
	filled = newState;
}
