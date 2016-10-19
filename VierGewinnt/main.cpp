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
	string firstPlayer, secondPlayer, mode;
	int depth = 0;
	AiMode aimode;

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

	if (input.cmdOptionExists("--depth"))
	{
		depth = stoi(input.getCmdOption("--depth"));
	}
	else
	{
		cout << "No depth chosen. Set standard depth: 10." << endl;
		depth = 10;
	}

	if (input.cmdOptionExists("--mode"))
	{
		mode = input.getCmdOption("--mode");
	}
	else
	{
		cout << "No mode chosen. Set standard mode: AlphaBeta." << endl;
		mode = "AlphaBeta";
	}

	if(mode == "NoDepth" || mode == "0")
	{
		aimode = NoDepth;
	} else if(mode == "DepthHeuristik" || mode == "1")
	{
		aimode = DepthHeuristik;
	} else if(mode == "AlphaBeta" || mode == "2")
	{
		aimode = AlphaBeta;
	} else
	{
		aimode = AlphaBeta;
	}

	if(firstPlayer == "ai")
	{
		players.push_back(new AiPlayer(PLAYER1, PLAYER2, depth, aimode));
	} else if (firstPlayer == "human")
	{
		players.push_back(new HumanPlayer(PLAYER1, PLAYER2));
	} else
	{
		cerr << "--first must be followed by 'ai' or 'human'" << endl;
		return false;
	}

	if(secondPlayer == "ai")
	{
		players.push_back(new AiPlayer(PLAYER2, PLAYER1, depth, aimode));
	} else if (secondPlayer == "human")
	{
		players.push_back(new HumanPlayer(PLAYER2, PLAYER1));
	} else
	{
		cerr << "--second must be followed by 'ai' or 'human'" << endl;
		return false;
	}

	cout << endl;

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
