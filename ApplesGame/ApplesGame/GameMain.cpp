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

	sf::Text scoreText;
	sf::Font scoreTextFont;

	sf::Text gameOverText;
	sf::Font gameOverTextfont;
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

	gameState.scoreTextFont.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Bold.ttf");
	float scoreTextXCoordinate = 2.5f;
	float scoreTextYCoordinate = 2.5f;
	gameState.scoreText.setFont(gameState.scoreTextFont);
	gameState.scoreText.setCharacterSize(24);
	gameState.scoreText.setFillColor(sf::Color::Yellow);
	gameState.scoreText.setString("Score: 0");
	gameState.scoreText.setPosition(scoreTextXCoordinate, scoreTextYCoordinate);

	// Declare & init game over text ui 

	gameState.gameOverTextfont.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Bold.ttf");
	float gameOverTextXCoordinate = SCREEN_WIDTH / 2.f - 55.5f;
	float gameOverTextYCoordinate = SCREEN_HEIGHT / 2.f - 55.5f;
	gameState.gameOverText.setFont(gameState.scoreTextFont);
	gameState.gameOverText.setCharacterSize(32);
	gameState.gameOverText.setFillColor(sf::Color::Red);
	gameState.gameOverText.setString("GAME OVER");
	gameState.gameOverText.setPosition(gameOverTextXCoordinate, gameOverTextYCoordinate);
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

	GameState gameState;
	InitGame(gameState);
	

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
			gameState.playerDirection = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			// 1 - Up
			gameState.playerDirection = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// 2 - Left
			gameState.playerDirection = PlayerDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			// 3 - down
			gameState.playerDirection = PlayerDirection::Down;
		}


		// Update player state
		switch (gameState.playerDirection)
		{
			case PlayerDirection::Right:
			{
				gameState.playerPosition.x += gameState.playerSpeed * deltaTime;
				break;
			}
			case PlayerDirection::Up:
			{
				gameState.playerPosition.y -= gameState.playerSpeed * deltaTime;
				break;
			}
			case PlayerDirection::Left:
			{
				gameState.playerPosition.x -= gameState.playerSpeed * deltaTime;
				break;
			}
			case PlayerDirection::Down:
			{
				gameState.playerPosition.y += gameState.playerSpeed * deltaTime;
				break;
			}
		}

		// Check screen borders
		if (gameState.playerPosition.x - PLAYER_SIZE / 2.f < 0.f || gameState.playerPosition.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
			gameState.playerPosition.y - PLAYER_SIZE / 2.f < 0.f || gameState.playerPosition.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
		{
			window.draw(gameState.gameOverText);
			window.display();

			// Pause 2 second
			sf::sleep(sf::seconds(1));

			// Reset player: coordinate, speed, direction. Reset eaten apples
			gameState.playerPosition.x = SCREEN_WIDTH / 2;
			gameState.playerPosition.y = SCREEN_HEIGHT / 2;
			gameState.playerDirection = PlayerDirection::Right;
			gameState.playerSpeed = INITIAL_SPEED;
			gameState.numEatenApples = 0;

			// Reset apple
			for (int i = 0; i < NUM_APPLES; ++i)
			{
				// Reset apple State
				gameState.isAppleEaten[i] = false;
				gameState.applePosition[i].x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
				gameState.applePosition[i].y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;

				// Reset apple shape
				gameState.appleShape[i].setPosition(gameState.applePosition[i].x, gameState.applePosition[i].y);
			}

			// Reset stone
			for (int i = 0; i < NUM_STONES; ++i)
			{
				// Reset stone State
				gameState.stonePosition[i].x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
				gameState.stonePosition[i].y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;

				// Reset stone shape
				gameState.stoneShape[i].setPosition(gameState.stonePosition[i].x, gameState.stonePosition[i].y);
			}

			// Reset score text UI
			gameState.scoreText.setString("Score: 0");
		}

		// Check apple colliders
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			if (!gameState.isAppleEaten[i])
			{
				float squareDistance = (gameState.playerPosition.x - gameState.applePosition[i].x) * (gameState.playerPosition.x - gameState.applePosition[i].x) +
					(gameState.playerPosition.y - gameState.applePosition[i].y) * (gameState.playerPosition.y - gameState.applePosition[i].y);
				float squareRadiusSum = (APPLE_SIZE + PLAYER_SIZE) * (APPLE_SIZE + PLAYER_SIZE) / 4;

				if (squareDistance <= squareRadiusSum)
				{
					gameState.isAppleEaten[i] = true;
					++gameState.numEatenApples;
					gameState.playerSpeed += ACCELERATION;
				}
			}
		}

		// Check stone colliders
		for (int i = 0; i < NUM_STONES; ++i)
		{
			float deltaX = fabs(gameState.playerPosition.x - gameState.stonePosition[i].x);
			float deltaY = fabs(gameState.playerPosition.y - gameState.stonePosition[i].y);

			if (deltaX <= (STONE_SIZE + PLAYER_SIZE) / 2.f &&
				deltaY <= (STONE_SIZE + PLAYER_SIZE) / 2.f)
			{
				window.close();
			}
		}

		// Update ScoreText state
		for (int i = 0; i < gameState.numEatenApples; ++i)
		{
			gameState.scoreText.setString("Score: " + std::to_string(gameState.numEatenApples));

		}

		window.clear();
		gameState.playerShape.setPosition(gameState.playerPosition.x, gameState.playerPosition.y);

		for (int i = 0; i < NUM_APPLES; ++i)
		{
			if (!gameState.isAppleEaten[i])
			{
				window.draw(gameState.appleShape[i]);
			}
			else {
				// Init apple state
				gameState.isAppleEaten[i] = false;
				gameState.applePosition[i].x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
				gameState.applePosition[i].y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;

				// Init apple shape
				gameState.appleShape[i].setPosition(gameState.applePosition[i].x, gameState.applePosition[i].y);
				window.draw(gameState.appleShape[i]);
			}
		}

		for (int i = 0; i < NUM_STONES; ++i)
		{
			window.draw(gameState.stoneShape[i]);
		}

		window.draw(gameState.playerShape);
		window.draw(gameState.scoreText);
		window.display();
	}

	return 0;
}
