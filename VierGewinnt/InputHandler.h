#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameManager.h"

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	void handleInput(sf::RenderWindow* window, GameManager* manager);
	void handleKeyEvent(sf::Event* event, sf::RenderWindow*	window, GameManager* manager);

private:
	bool keyPressed;
};
