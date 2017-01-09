/*
	SFML Games Programming Project
	Written by Charlie Gillies
	Source viewable at https://github.com/charliegillies/SFMLGamesProject
*/

#include <SFML/Graphics.hpp>

int main()
{
	// window settings
	const int width = 1280;
	const int height = 720;
	const char* title = "SFML Games Project";

	// create the window with the appropiate settings
	sf::RenderWindow window(sf::VideoMode(width, height), title);

	while (window.isOpen())
	{
		// poll events to see if the window has been closed		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// clear everything in the window
		window.clear();

		// draw & update here..


		// display everything in the window
		window.display();
	}

	return 0;
}