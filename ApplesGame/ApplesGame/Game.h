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
		Rectangle screenRect;
		Player player;
		Apple apple[SetRandomNumberApples()];
		Stone stone[NUM_STONES];

		// Global game data
		int numEatenApples;
		float deltaTime;
		bool isGameFinished = false;
		float timeSinceGameFinish = 0.f;
		sf::Sound appleEatSound;
		sf::Sound deathSound;
		sf::RectangleShape background;

		// Resources
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture stoneTexture;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;

		// UI data
		sf::Font font;
		sf::Text scoreText;
		sf::Text controlsHintText;
		sf::Text gameOverText;
		sf::Text gameOverScoreText;
	};

	void InitGame(Game& game);
	void UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void StartPlayingState(Game& game);
	void UpdatePlayingState(Game& game, float deltaTime);
	void StartGameoverState(Game& game);
	void UpdateGameoverState(Game& game, float deltaTime);
}
