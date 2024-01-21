#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Apple.h"
#include "Stone.h"

namespace ApplesGame
{
	struct Game
	{
		Player player;
		Apple apple[NUM_APPLES];
		Stone stone[NUM_STONES];

		// Global game data
		int numEatenApples;
		float deltaTime;
		bool isGameFinished = false;
		sf::Sound appleEatSound;
		sf::Sound deathSound;

		// Resources
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture stoneTexture;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;

		// UI data
		sf::Text scoreText;
		sf::Font scoreTextFont;
		sf::Text gameOverText;
		sf::Font gameOverTextfont;
		float scoreTextXCoordinate;
		float scoreTextYCoordinate;
		float gameOverTextXCoordinate;
		float gameOverTextYCoordinate;
	};
}
