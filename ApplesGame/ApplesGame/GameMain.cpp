#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int NUM_APPLES = 15;
const int NUM_STONES = 5;
const float PLAYER_SIZE = 20.f;
const float APPLE_SIZE = 20.f;
const float STONE_SIZE = 20.f;
const float INITIAL_SPEED = 100.f;
const float ACCELERATION = 20.5f;

struct Vector2D
{
	float x = 0;
	float y = 0;
};

typedef Vector2D Position2D;

enum class PlayerDirection : int
{
	Right = 0,
	Up,
	Left,
	Down
};

struct GameState
{
	// Player data
	Position2D playerPosition;
	float playerSpeed = INITIAL_SPEED;
	PlayerDirection playerDirection = PlayerDirection::Right;
	sf::RectangleShape playerShape;

	// Apples data
	Position2D applePosition[NUM_APPLES];
	sf::CircleShape appleShape[NUM_APPLES];

	// Stone data
	Position2D stonePosition[NUM_STONES];
	sf::RectangleShape stoneShape[NUM_STONES];

	// Global game data
	int numEatenApples = 0;
	bool isAppleEaten[NUM_APPLES];
};

void InitGame(GameState& gameState)
{
	// Init eaten apple counter.
	gameState.numEatenApples = 0;

	// Init player state
	gameState.playerPosition = { SCREEN_WIDTH / 2.f , SCREEN_HEIGHT / 2.f };
	gameState.playerSpeed = INITIAL_SPEED;
	gameState.playerDirection = PlayerDirection::Right;

	// Init player shape
	gameState.playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	gameState.playerShape.setFillColor(sf::Color::Red);
	gameState.playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
	gameState.playerShape.setPosition(gameState.playerPosition.x, gameState.playerPosition.y);

	// Init apple state & init apple shape
	for (int i = 0; i < NUM_APPLES; ++i)
	{
		// Apple State
		gameState.isAppleEaten[i] = false;
		gameState.applePosition[i].x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
		gameState.applePosition[i].y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;

		// Apple shape
		gameState.appleShape[i].setRadius(APPLE_SIZE / 2.f);
		gameState.appleShape[i].setFillColor(sf::Color::Green);
		gameState.appleShape[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
		gameState.appleShape[i].setPosition(gameState.applePosition[i].x, gameState.applePosition[i].y);
	}

	// Init stone state & init stone shape
	for (int i = 0; i < NUM_STONES; ++i)
	{
		// stone State
		gameState.stonePosition[i].x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
		gameState.stonePosition[i].y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;

		// stone shape
		gameState.stoneShape[i].setSize(sf::Vector2f(STONE_SIZE, STONE_SIZE));
		gameState.stoneShape[i].setFillColor(sf::Color::White);
		gameState.stoneShape[i].setOrigin(STONE_SIZE / 2.f, STONE_SIZE / 2.f);
		gameState.stoneShape[i].setPosition(gameState.stonePosition[i].x, gameState.stonePosition[i].y);
	}

	// Declare & init score text ui 
	sf::Text scoreText;
	sf::Font scoreTextFont;
	scoreTextFont.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Bold.ttf");
	float scoreTextXCoordinate = 2.5f;
	float scoreTextYCoordinate = 2.5f;
	scoreText.setFont(scoreTextFont);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::Yellow);
	scoreText.setString("Score: 0");
	scoreText.setPosition(scoreTextXCoordinate, scoreTextYCoordinate);

	// Declare & init game over text ui 
	sf::Text gameOverText;
	sf::Font gameOverTextfont;
	gameOverTextfont.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Bold.ttf");
	float gameOverTextXCoordinate = SCREEN_WIDTH / 2.f - 55.5f;
	float gameOverTextYCoordinate = SCREEN_HEIGHT / 2.f - 55.5f;
	gameOverText.setFont(scoreTextFont);
	gameOverText.setCharacterSize(32);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setString("GAME OVER");
	gameOverText.setPosition(gameOverTextXCoordinate, gameOverTextYCoordinate);
}

int main()
{
	// Init seed for random func
	int seed = (int)time(nullptr);
	srand(seed);

	// Init game clock
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	// Init Window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game by DJEAKE <3");

	

	// Main Loop
	while (window.isOpen())
	{
		// Calculate time delta
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Read events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Handle input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{	// 0 - Right
			playerDirection = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			// 1 - Up
			playerDirection = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// 2 - Left
			playerDirection = PlayerDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			// 3 - down
			playerDirection = PlayerDirection::Down;
		}


		// Update player state
		switch (playerDirection)
		{
			case PlayerDirection::Right:
			{
				playerPosition.x += playerSpeed * deltaTime;
				break;
			}
			case PlayerDirection::Up:
			{
				playerPosition.y -= playerSpeed * deltaTime;
				break;
			}
			case PlayerDirection::Left:
			{
				playerPosition.x -= playerSpeed * deltaTime;
				break;
			}
			case PlayerDirection::Down:
			{
				playerPosition.y += playerSpeed * deltaTime;
				break;
			}
		}

		// Check screen borders
		if (playerPosition.x - PLAYER_SIZE / 2.f < 0.f || playerPosition.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
			playerPosition.y - PLAYER_SIZE / 2.f < 0.f || playerPosition.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
		{
			window.draw(gameOverText);
			window.display();

			// Pause 2 second
			sf::sleep(sf::seconds(1));

			// Reset player: coordinate, speed, direction. Reset eaten apples
			playerPosition.x = SCREEN_WIDTH / 2;
			playerPosition.y = SCREEN_HEIGHT / 2;
			playerDirection = PlayerDirection::Right;
			playerSpeed = INITIAL_SPEED;
			numEatenApples = 0;

			// Reset apple
			for (int i = 0; i < NUM_APPLES; ++i)
			{
				// Reset apple State
				isAppleEaten[i] = false;
				applePosition[i].x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
				applePosition[i].y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;

				// Reset apple shape
				appleShape[i].setPosition(applePosition[i].x, applePosition[i].y);
			}

			// Reset stone
			for (int i = 0; i < NUM_STONES; ++i)
			{
				// Reset stone State
				stonePosition[i].x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
				stonePosition[i].y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;

				// Reset stone shape
				stoneShape[i].setPosition(stonePosition[i].x, stonePosition[i].y);
			}

			// Reset score text UI
			scoreText.setString("Score: 0");
		}

		// Check apple colliders
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			if (!isAppleEaten[i])
			{
				float squareDistance = (playerPosition.x - applePosition[i].x) * (playerPosition.x - applePosition[i].x) +
					(playerPosition.y - applePosition[i].y) * (playerPosition.y - applePosition[i].y);
				float squareRadiusSum = (APPLE_SIZE + PLAYER_SIZE) * (APPLE_SIZE + PLAYER_SIZE) / 4;

				if (squareDistance <= squareRadiusSum)
				{
					isAppleEaten[i] = true;
					++numEatenApples;
					playerSpeed += ACCELERATION;
				}
			}
		}

		// Check stone colliders
		for (int i = 0; i < NUM_STONES; ++i)
		{
			float deltaX = fabs(playerPosition.x - stonePosition[i].x);
			float deltaY = fabs(playerPosition.y - stonePosition[i].y);

			if (deltaX <= (STONE_SIZE + PLAYER_SIZE) / 2.f &&
				deltaY <= (STONE_SIZE + PLAYER_SIZE) / 2.f)
			{
				window.close();
			}
		}

		// Update ScoreText state
		for (int i = 0; i < numEatenApples; ++i)
		{
			scoreText.setString("Score: " + std::to_string(numEatenApples));

		}

		window.clear();
		playerShape.setPosition(playerPosition.x, playerPosition.y);

		for (int i = 0; i < NUM_APPLES; ++i)
		{
			if (!isAppleEaten[i])
			{
				window.draw(appleShape[i]);
			}
			else {
				// Init apple state
				isAppleEaten[i] = false;
				applePosition[i].x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
				applePosition[i].y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;

				// Init apple shape
				appleShape[i].setPosition(applePosition[i].x, applePosition[i].y);
				window.draw(appleShape[i]);
			}
		}

		for (int i = 0; i < NUM_STONES; ++i)
		{
			window.draw(stoneShape[i]);
		}

		window.draw(playerShape);
		window.draw(scoreText);
		window.display();
	}

	return 0;
}
