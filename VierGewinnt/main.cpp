#include "SFML/Graphics.hpp"
#include "Board.h"
#include "GameManager.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "AiPlayer.h"

sf::RenderWindow* window;
GameManager* gameManager;
std::vector<Player*> players;

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

	//Init
	players.push_back(new HumanPlayer(PLAYER1, PLAYER2));
	players.push_back(new AiPlayer(PLAYER2, PLAYER1));
	//players.push_back(new AiPlayer(PLAYER1, PLAYER2));
	gameManager = new GameManager(7, 6, players);


	while(window->isOpen())
	{
		window->clear();

		if(winCondition)
		{
			winCondition = gameManager->Run(window);
		} else
		{
			sf::Event event;
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window->close();
				}
				else if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Key::Escape)
					{
						window->close();
					}
				}
			}
		}
		gameManager->Render(window);

		window->display();
	}

	ReleaseStuff();

	return 0;
}
