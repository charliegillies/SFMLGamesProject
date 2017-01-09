/*
	SFML Games Programming Project
	Written by Charlie Gillies
	Source viewable at https://github.com/charliegillies/SFMLGamesProject
*/

#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	// window settings
	const int width = 1280;
	const int height = 720;
	const char* title = "SFML Games Project";

	// create the window with the appropiate settings
	sf::RenderWindow window(sf::VideoMode(width, height), title);
	
	// create the game instance
	Game game;
	// inform game that we're starting initialization
	game.onStart();

	while (window.isOpen())
	{
		// poll events to see if the window has been closed		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// inform the game that we're exiting
				game.onExit();
				// inform the window that we're exiting
				window.close();
			}
		}

		// clear everything in the window
		window.clear();

		// update the game
		game.onUpdate();

		// display everything in the window
		window.display();
	}

	return 0;
}