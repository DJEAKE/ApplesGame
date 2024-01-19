
#include <cassert>
#include "Math.h"
#include "Player.h"
#include "Constans.h"
#include "Apple.h"
#include "Stone.h"
#include "Game.h"

using namespace ApplesGame;

void RestartGame(Game& game)
{
	// Init eaten apple counter.
	game.numEatenApples = 0;
	game.isGameFinished = false;

	InitPlayer(game.player, game);

	// Init apple state & init apple shape
	for (int i = 0; i < NUM_APPLES; ++i)
	{
		InitApple(game.apple[i], game);
		game.apple[i].isAppleEaten = false;
	};

	// Init stone state & init stone shape
	for (int i = 0; i < NUM_STONES; ++i)
	{
		InitStone(game.stone[i], game);
	};
}

void InitGame(Game& game)
{
	assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
	assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
	assert(game.stoneTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));
	assert(game.eatAppleSoundBuffer.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
	assert(game.gameOverSoundBuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"));

	// Init score text ui 
	game.scoreTextFont.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Bold.ttf");
	game.scoreTextXCoordinate = 2.5f;
	game.scoreTextYCoordinate = 2.5f;
	game.scoreText.setFont(game.scoreTextFont);
	game.scoreText.setCharacterSize(24);
	game.scoreText.setFillColor(sf::Color::Yellow);
	game.scoreText.setString("Score: 0");
	game.scoreText.setPosition(game.scoreTextXCoordinate, game.scoreTextYCoordinate);

	// Init game over text ui 
	game.gameOverTextfont.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Bold.ttf");
	game.gameOverTextXCoordinate = SCREEN_WIDTH / 2.f - 55.5f;
	game.gameOverTextYCoordinate = SCREEN_HEIGHT / 2.f - 55.5f;
	game.gameOverText.setFont(game.scoreTextFont);
	game.gameOverText.setCharacterSize(32);
	game.gameOverText.setFillColor(sf::Color::Red);
	game.gameOverText.setString("GAME OVER");
	game.gameOverText.setPosition(game.gameOverTextXCoordinate, game.gameOverTextYCoordinate);

	RestartGame(game);
};

void UpdateGame(Game& game, float deltaTime)
{
	if (!game.isGameFinished)
	{
		// Handle input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{	// 0 - Right
			game.player.playerDirection = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			// 1 - Up
			game.player.playerDirection = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// 2 - Left
			game.player.playerDirection = PlayerDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			// 3 - down
			game.player.playerDirection = PlayerDirection::Down;
		}

		// Update player state
		switch (game.player.playerDirection)
		{
		case PlayerDirection::Right:
		{
			game.player.playerPosition.x += game.player.playerSpeed * game.deltaTime;
			break;
		}
		case PlayerDirection::Up:
		{
			game.player.playerPosition.y -= game.player.playerSpeed * game.deltaTime;
			break;
		}
		case PlayerDirection::Left:
		{
			game.player.playerPosition.x -= game.player.playerSpeed * game.deltaTime;
			break;
		}
		case PlayerDirection::Down:
		{
			game.player.playerPosition.y += game.player.playerSpeed * game.deltaTime;
			break;
		}
		}

		// Check screen borders
		if (game.player.playerPosition.x - PLAYER_SIZE / 2.f < 0.f || game.player.playerPosition.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
			game.player.playerPosition.y - PLAYER_SIZE / 2.f < 0.f || game.player.playerPosition.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
		{
			//gawindow.draw(game.gameOverText);
			//window.display();

			// Pause 2 second
			sf::sleep(sf::seconds(1));

			// Reset player: coordinate, speed, direction. Reset eaten apples
			game.player.playerPosition.x = (float)SCREEN_WIDTH / 2;
			game.player.playerPosition.y = (float)SCREEN_HEIGHT / 2;
			game.player.playerDirection = PlayerDirection::Right;
			game.player.playerSpeed = INITIAL_SPEED;
			game.numEatenApples = 0;

			// Reset apple
			for (int i = 0; i < NUM_APPLES; ++i)
			{
				// Reset apple State
				game.apple[i].isAppleEaten = false;
				game.apple[i].applePosition = GetRandomPositioInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

				// Reset apple shape
				game.apple[i].sprite.setPosition(game.apple[i].applePosition.x, game.apple[i].applePosition.y);
			}

			// Reset stone
			for (int i = 0; i < NUM_STONES; ++i)
			{
				// Reset stone State
				game.stone[i].stonePosition = GetRandomPositioInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

				// Reset stone shape
				game.stone[i].sprite.setPosition(game.stone[i].stonePosition.x, game.stone[i].stonePosition.y);
			}

			// Reset score text UI
			game.scoreText.setString("Score: 0");
		}

		// Check apple colliders
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			if (!game.apple[i].isAppleEaten)
			{
				if (IsCircleCollide(game.player.playerPosition, PLAYER_SIZE, game.apple[i].applePosition, APPLE_SIZE / 2.f))
				{
					game.apple[i].isAppleEaten = true;
					++game.numEatenApples;
					game.player.playerSpeed += ACCELERATION;
				}
			}
			else
			{
				game.apple[i].isAppleEaten = false;
				game.apple[i].applePosition = GetRandomPositioInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
			}
		}

		// Check stone colliders
		for (int i = 0; i < NUM_STONES; ++i)
		{
			if (IsRectanglesCollide(game.player.playerPosition, { PLAYER_SIZE, PLAYER_SIZE }, game.stone[i].stonePosition, { STONE_SIZE, STONE_SIZE }))
			{
				game.isGameFinished = true;
				RestartGame(game);
			}
		}

		// Update ScoreText state
		for (int i = 0; i < game.numEatenApples; ++i)
		{
		}
	}
}

void DrawGame(Game& game, sf::RenderWindow& window)
{
	DrawPlayer(game.player, window);
	game.scoreText.setString("Score: " + std::to_string(game.numEatenApples));
	window.draw(game.scoreText);
	game.gameOverText.setPosition(game.gameOverTextXCoordinate, game.gameOverTextYCoordinate);
	// window.draw(game.gameOverText);

	for (int i = 0; i < NUM_APPLES; ++i)
	{
		game.apple[i].sprite.setPosition(game.apple[i].applePosition.x, game.apple[i].applePosition.y);
		window.draw(game.apple[i].sprite);
	}

	for (int i = 0; i < NUM_STONES; ++i)
	{
		game.stone[i].sprite.setPosition(game.stone[i].stonePosition.x, game.stone[i].stonePosition.y);
		window.draw(game.stone[i].sprite);
	}
}

int main()
{
	// Init seed for random func
	int seed = (int)time(nullptr);
	srand(seed);

	// Init Window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game by DJEAKE <3");

	Game game;
	InitGame(game);
	Player player;

	// Init game clock
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	// Main Loop
	while (window.isOpen())
	{
		// Reduce framerate to not spam CPU and GPU
		sf::sleep(sf::microseconds(16));

		// Calculate Time
		float currentTime = gameClock.getElapsedTime().asSeconds();
		game.deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Read events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		UpdateGame(game, game.deltaTime);
		window.clear();
		DrawGame(game, window);
		window.display();
	}
	return 0;
}