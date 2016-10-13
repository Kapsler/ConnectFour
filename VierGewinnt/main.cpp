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
	bool winCondition = true;

	window = new sf::RenderWindow(sf::VideoMode(700, 600), "Vier Gewinnt");
	window->setKeyRepeatEnabled(false);

	gameManager = new GameManager(7, 6);
	input = new InputHandler();

	while(window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			} else if(event.type == sf::Event::KeyPressed)
			{
				if(winCondition)
				{
					input->handleKeyEvent(&event, window, gameManager);
				} else
				{
					if (event.key.code == sf::Keyboard::Key::Escape)
					{
						window->close();
					}
				}
			}
		}

		window->clear();

		if(winCondition)
		{
			winCondition = gameManager->Run();
		}
		gameManager->Render(window);

		window->display();
	}

	ReleaseStuff();

	return 0;
}
