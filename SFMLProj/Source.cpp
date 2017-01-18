/*
	SFML Games Programming Project
	Written by Charlie Gillies
	Source viewable at https://github.com/charliegillies/SFMLGamesProject
*/

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "MenuScene.h"

int main()
{
	// window settings
	const int width = 1280;
	const int height = 720;
	const char* title = "Sailor";

	// create the window with the appropiate settings
	sf::RenderWindow window(sf::VideoMode(width, height), title);
	
	// create the game instance
	Game* game = new Game(new MenuScene(), window);
	// inform game that we're starting initialization
	game->onStart();

	sf::Clock clock;
	float fps = 60;
	float time = 1 / fps;

	Input* input = game->getInput();
	KeyboardState kb_state{};
	MouseState m_state{};

	while (window.isOpen())
	{
		// poll events to see if the window has been closed		
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				// on the window being closed
			case sf::Event::Closed:
			{
				// inform the game that we're exiting
				game->onExit();
				// inform the window that we're exiting
				window.close();
			}
			break;

				// on a key being pressed
			case sf::Event::KeyPressed:
			{
				sf::Keyboard::Key p_code = event.key.code;
				kb_state.keys[p_code] = true;
			}
			break;

				// on a key being released
			case sf::Event::KeyReleased:
			{
				sf::Keyboard::Key r_code = event.key.code;
				kb_state.keys[r_code] = false;
			}
			break;


			case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
					m_state.leftClicked = true;

				if (event.mouseButton.button == sf::Mouse::Right)
					m_state.rightClicked = true;
			}
			break;

			case sf::Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
					m_state.leftClicked = false;

				if (event.mouseButton.button == sf::Mouse::Right)
					m_state.rightClicked = false;
			}
			break;

			case sf::Event::MouseMoved:
			{
				m_state.screenX = event.mouseMove.x;
				m_state.screenY = event.mouseMove.y;
			}
			break;

				//switch end
			}
		}

		float dt = clock.getElapsedTime().asSeconds();

		if (dt >= time)
		{
			// set deltaTime
			game->setDt(dt);

			// clear everything in the window
			window.clear();

			// set the keyboard state from the event info
			input->setKeyboardState(kb_state);
			// set the mouse state from the event info
			input->setMouseState(m_state);

			// update the game
			game->onUpdate();

			game->setDebugValue("dt", to_string(dt));

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