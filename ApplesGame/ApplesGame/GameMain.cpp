﻿#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constans.h"
#include "Game.h"
#include "GameMode.h"

int main()
{
	using namespace ApplesGame;

	int seed = (int)time(nullptr);
	srand(seed);

	// Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game! by DJEAKE");

	// Game initialization
	Game game;
	InitGame(game);

	// Init game clocks
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();
	
	// Main loop
	while (window.isOpen())
	{
		// Reduce framerate to not spam CPU and GPU
		sf::sleep(sf::milliseconds(16));

		// Calculate time delta
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Read events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				window.close();
				break;
			}
		}

		// The game will not update its state until the player selects the necessary settings for the game
		if (game.isSettingSelected == true)
		{
			UpdateGame(game, deltaTime);
		}

		// Draw game
		window.clear();
		DrawGame(game, window);
		window.display();
	}

	return 0;
}
