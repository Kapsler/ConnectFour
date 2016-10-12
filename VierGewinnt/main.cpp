#include "SFML/Graphics.hpp"
#include "Board.h"
#include "InputHandler.h"
#include "GameManager.h"

sf::RenderWindow* window;
GameManager* gameManager;
InputHandler* input;

void ReleaseStuff()
{
	delete gameManager;
	delete window;
}

int main()
{
	window = new sf::RenderWindow(sf::VideoMode(700, 600), "Vier Gewinnt");
	window->setKeyRepeatEnabled(false);

	gameManager = new GameManager(7, 6);
	input = new InputHandler();

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			} else if( event.type == sf::Event::KeyPressed)
			{
				input->handleKeyEvent(&event, window, gameManager);
			}
		}

		window->clear();

		if(!gameManager->Run(window))
		{
			window->close();
		}

		window->display();
	}

	ReleaseStuff();

	return 0;
}
