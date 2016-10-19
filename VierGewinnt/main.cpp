#include "SFML/Graphics.hpp"
#include "Board.h"
#include "GameManager.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "AiPlayer.h"
#include "CommandLineParser.h"

sf::RenderWindow* window;
GameManager* gameManager;
std::vector<Player*> players;

void ReleaseStuff()
{
	delete gameManager;
	delete window;
}

bool handleParameters(int argc, char* argv[])
{
	CommandLineParser input(argc, argv);
	string firstPlayer, secondPlayer;

	if (input.cmdOptionExists("--first"))
	{
		firstPlayer = input.getCmdOption("--first");
	}
	else
	{
		cerr << "Parameter --first not found!" << endl;
		return false;
	}

	if (input.cmdOptionExists("--second"))
	{
		secondPlayer = input.getCmdOption("--second");
	}
	else
	{
		cerr << "Parameter --first not found!" << endl;
		return false;
	}




	if(firstPlayer == "ai")
	{
		players.push_back(new AiPlayer(PLAYER1, PLAYER2));
	} else if (firstPlayer == "human")
	{
		players.push_back(new HumanPlayer(PLAYER1, PLAYER2));
	} else
	{
		std::cerr << "--first must be followed by 'ai' or 'human'" << std::endl;
		return false;
	}

	if(secondPlayer == "ai")
	{
		players.push_back(new AiPlayer(PLAYER2, PLAYER1));
	} else if (secondPlayer == "human")
	{
		players.push_back(new HumanPlayer(PLAYER2, PLAYER1));
	} else
	{
		std::cerr << "--second must be followed by 'ai' or 'human'" << std::endl;
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	bool winCondition = true;

	window = new sf::RenderWindow(sf::VideoMode(700, 600), "Vier Gewinnt");
	window->setKeyRepeatEnabled(false);

	if(!handleParameters(argc, argv))
	{
		return -1;
	}

	//Init
	//players.push_back(new HumanPlayer(PLAYER1, PLAYER2));
	//players.push_back(new AiPlayer(PLAYER2, PLAYER1));
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
			window->close();
			/*sf::Event event;
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
			}*/
		}
		gameManager->Render(window);

		window->display();
	}

	ReleaseStuff();

	return 0;
}
