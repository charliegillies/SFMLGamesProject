/*
	SFML Games Programming Project
	Written by Charlie Gillies
	Source viewable at https://github.com/charliegillies/SFMLGamesProject
*/

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "TestScene.h"
#include <iostream>

int main()
{
	// window settings
	const int width = 1280;
	const int height = 720;
	const char* title = "Sailor";

	// create the window with the appropiate settings
	sf::RenderWindow window(sf::VideoMode(width, height), title);
	
	// create the game instance
	Game* game = new Game(new TestScene(), window);
	// inform game that we're starting initialization
	game->onStart();

	sf::Clock clock;
	float fps = 60;
	float time = 1 / fps;

	while (window.isOpen())
	{
		// poll events to see if the window has been closed		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// inform the game that we're exiting
				game->onExit();
				// inform the window that we're exiting
				window.close();
			}
		}

		float dt = clock.getElapsedTime().asSeconds();

		if (dt >= time)
		{
			// set deltaTime
			game->setDt(dt);

			// clear everything in the window
			window.clear();

			// update the game
			game->onUpdate();

			// render the game
			game->onRender();

			// display everything in the window
			window.display();

			// restart the clock
			clock.restart();
		}
	}

	return 0;
}