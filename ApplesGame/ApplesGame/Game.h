#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Apple.h"
#include "Stone.h"
#include <unordered_map>

namespace ApplesGame
{
	struct Game
	{
		Rectangle screenRect;
		Player player;
		std::vector<Apple> apples;
		Stone stone[NUM_STONES];
		std::unordered_map<std::string, int> recordsTable;

		// Global game data
		int numApples = SetRandomNumberApples();
		int numEatenApples = 0;
		int GameModeSettings = 0;
		float deltaTime;
		float timeSinceGameFinish = 0.f;
		bool isGameFinished = false;
		bool isSettingSelected = false;
		bool isInfiniteAppleCount = true;

		// Resources
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture stoneTexture;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;
		sf::Sound appleEatSound;
		sf::Sound deathSound;
		sf::RectangleShape background;

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
