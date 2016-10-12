#include "InputHandler.h"

InputHandler::InputHandler()
{

}

InputHandler::~InputHandler()
{

}

void InputHandler::handleInput(sf::RenderWindow* window, GameManager* manager)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		window->close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		manager->SelectSlotRight();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		manager->SelectSlotLeft();
	}


}

void InputHandler::handleKeyEvent(sf::Event* event, sf::RenderWindow* window, GameManager* manager)
{
	if(event->key.code == sf::Keyboard::Key::Escape)
	{
		window->close();
	}
	if(event->key.code == sf::Keyboard::Key::Right)
	{
		manager->SelectSlotRight();
	}
	if(event->key.code == sf::Keyboard::Key::Left)
	{
		manager->SelectSlotLeft();
	}
	if(event->key.code == sf::Keyboard::Key::Space)
	{
		manager->PutTokenInSlot();
	}
}
