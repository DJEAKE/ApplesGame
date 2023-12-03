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

Position2D GetRandomPositioInScreen()
{
	Position2D result;
	result.x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
	result.y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;
	return result;
}

bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Vector2D rect2Size)
{
	float deltaX = fabs(rect1Position.x - rect2Position.x);
	float deltaY = fabs(rect1Position.y - rect2Position.y);
	return (deltaX <= (rect2Size.x + rect1Size.x) / 2.f && deltaY <= (rect2Size.y + rect1Size.y) / 2.f);
}

bool IsCircleCollide(Position2D circle1Position, float circle1Radius, Position2D circle2Position, float circle2Radius)
{
	const auto distanceX = circle1Position.x - circle2Position.x;
	const auto distanceY = circle1Position.y - circle2Position.y;
	const auto squareDistance = distanceX * distanceX + distanceY * distanceY;
	float squareRadiusSum = (circle1Radius + circle2Radius) * (circle1Radius + circle2Radius) / 4;
	return (squareDistance <= squareRadiusSum);
}
enum class PlayerDirection : int
{
	Right = 0,
	Up,
	Left,
	Down
};

struct GameState
{
	Player player;
	Apple apple[NUM_APPLES];
	// Stone data
	Position2D stonePosition[NUM_STONES];
	sf::RectangleShape stoneShape[NUM_STONES];

	// Global game data
	int numEatenApples;
	float deltaTime;
	bool isGameFinished;

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

struct Player
{
	// Player data
	Position2D playerPosition;
	PlayerDirection playerDirection = PlayerDirection::Right;;
	sf::RectangleShape playerShape;
	float playerSpeed = INITIAL_SPEED;
};

struct Apple
{
	// Apples data
	Position2D applePosition[NUM_APPLES];
	sf::CircleShape appleShape[NUM_APPLES];
	bool isAppleEaten[NUM_APPLES];
};

void InitPlayer(Player& player)
{
	// Init player state
	player.playerPosition = { SCREEN_WIDTH / 2.f , SCREEN_HEIGHT / 2.f };
	player.playerSpeed = INITIAL_SPEED;
	player.playerDirection = PlayerDirection::Right;

	// Init player shape
	player.playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	player.playerShape.setFillColor(sf::Color::Red);
	player.playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
	player.playerShape.setPosition(player.playerPosition.x, player.playerPosition.y);
}

void InitApple(Apple& apple)
{
	// Init apple state & init apple shape
	for (int i = 0; i < NUM_APPLES; ++i)
	{
		// Apple State
		apple.applePosition[i] = GetRandomPositioInScreen();
		apple.isAppleEaten[i] = false;

		// Apple shape
		apple.appleShape[i].setRadius(APPLE_SIZE / 2.f);
		apple.appleShape[i].setFillColor(sf::Color::Green);
		apple.appleShape[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
		apple.appleShape[i].setPosition(apple.applePosition[i].x, apple.applePosition[i].y);
	}

}

void InitGame(GameState& gameState)
{
	// Init eaten apple counter.
	gameState.numEatenApples = 0;
	gameState.isGameFinished = false;

	// Init stone state & init stone shape
	for (int i = 0; i < NUM_STONES; ++i)
	{
		// stone State
		gameState.stonePosition[i] = GetRandomPositioInScreen();

		// stone shape
		gameState.stoneShape[i].setSize(sf::Vector2f(STONE_SIZE, STONE_SIZE));
		gameState.stoneShape[i].setFillColor(sf::Color::White);
		gameState.stoneShape[i].setOrigin(STONE_SIZE / 2.f, STONE_SIZE / 2.f);
		gameState.stoneShape[i].setPosition(gameState.stonePosition[i].x, gameState.stonePosition[i].y);
	}

	// Init score text ui 
	gameState.scoreTextFont.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Bold.ttf");
	gameState.scoreTextXCoordinate = 2.5f;
	gameState.scoreTextYCoordinate = 2.5f;
	gameState.scoreText.setFont(gameState.scoreTextFont);
	gameState.scoreText.setCharacterSize(24);
	gameState.scoreText.setFillColor(sf::Color::Yellow);
	gameState.scoreText.setString("Score: 0");
	gameState.scoreText.setPosition(gameState.scoreTextXCoordinate, gameState.scoreTextYCoordinate);

	// Init game over text ui 
	gameState.gameOverTextfont.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Bold.ttf");
	gameState.gameOverTextXCoordinate = SCREEN_WIDTH / 2.f - 55.5f;
	gameState.gameOverTextYCoordinate = SCREEN_HEIGHT / 2.f - 55.5f;
	gameState.gameOverText.setFont(gameState.scoreTextFont);
	gameState.gameOverText.setCharacterSize(32);
	gameState.gameOverText.setFillColor(sf::Color::Red);
	gameState.gameOverText.setString("GAME OVER");
	gameState.gameOverText.setPosition(gameState.gameOverTextXCoordinate, gameState.gameOverTextYCoordinate);
}

void UpdateGame(GameState& gameState, float deltaTime)
{
	if (!gameState.isGameFinished)
	{
		// Handle input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{	// 0 - Right
			gameState.player.playerDirection = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			// 1 - Up
			gameState.player.playerDirection = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// 2 - Left
			gameState.player.playerDirection = PlayerDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			// 3 - down
			gameState.player.playerDirection = PlayerDirection::Down;
		}

		// Update player state
		switch (gameState.player.playerDirection)
		{
		case PlayerDirection::Right:
		{
			gameState.player.playerPosition.x += gameState.player.playerSpeed * gameState.deltaTime;
			break;
		}
		case PlayerDirection::Up:
		{
			gameState.player.playerPosition.y -= gameState.player.playerSpeed * gameState.deltaTime;
			break;
		}
		case PlayerDirection::Left:
		{
			gameState.player.playerPosition.x -= gameState.player.playerSpeed * gameState.deltaTime;
			break;
		}
		case PlayerDirection::Down:
		{
			gameState.player.playerPosition.y += gameState.player.playerSpeed * gameState.deltaTime;
			break;
		}
		}

		// Check screen borders
		if (gameState.player.playerPosition.x - PLAYER_SIZE / 2.f < 0.f || gameState.player.playerPosition.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
			gameState.player.playerPosition.y - PLAYER_SIZE / 2.f < 0.f || gameState.player.playerPosition.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
		{
			//gawindow.draw(gameState.gameOverText);
			//window.display();

			// Pause 2 second
			sf::sleep(sf::seconds(1));

			// Reset player: coordinate, speed, direction. Reset eaten apples
			gameState.player.playerPosition.x = SCREEN_WIDTH / 2;
			gameState.player.playerPosition.y = SCREEN_HEIGHT / 2;
			gameState.player.playerDirection = PlayerDirection::Right;
			gameState.player.playerSpeed = INITIAL_SPEED;
			gameState.numEatenApples = 0;

			// Reset apple
			for (int i = 0; i < NUM_APPLES; ++i)
			{
				// Reset apple State
				gameState.apple[i].isAppleEaten[i] = false;
				gameState.apple[i].applePosition[i] = GetRandomPositioInScreen();

				// Reset apple shape
				gameState.apple[i].appleShape.setPosition(gameState.apple[i].applePosition.x, gameState.apple[i].applePosition.y);
			}

			// Reset stone
			for (int i = 0; i < NUM_STONES; ++i)
			{
				// Reset stone State
				gameState.stonePosition[i] = GetRandomPositioInScreen();

				// Reset stone shape
				gameState.stoneShape[i].setPosition(gameState.stonePosition[i].x, gameState.stonePosition[i].y);
			}

			// Reset score text UI
			gameState.scoreText.setString("Score: 0");
		}

		// Check apple colliders
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			if (!gameState.apple[i].isAppleEaten[i])
			{
				if (IsCircleCollide(gameState.player.playerPosition, PLAYER_SIZE, gameState.apple[i].applePosition[i], APPLE_SIZE / 2.f))
				{
					gameState.apple[i].isAppleEaten[i] = true;
					++gameState.numEatenApples;
					gameState.player.playerSpeed += ACCELERATION;
				}
			}
			else
			{
				gameState.apple[i].isAppleEaten[i] = false;
				gameState.apple[i].applePosition[i] = GetRandomPositioInScreen();
			}
		}

		// Check stone colliders
		for (int i = 0; i < NUM_STONES; ++i)
		{
			if (IsRectanglesCollide(gameState.player.playerPosition, { PLAYER_SIZE, PLAYER_SIZE }, gameState.stonePosition[i], { STONE_SIZE, STONE_SIZE }))
			{
				gameState.isGameFinished = true;
			}
		}

		// Update ScoreText state
		for (int i = 0; i < gameState.numEatenApples; ++i)
		{
		}
	}
}

void DrawGame(GameState& gameState, sf::RenderWindow& window)
{
	player.playerShape.setPosition(player.playerPosition.x, player.playerPosition.y);
	window.draw(player.playerShape);
	gameState.scoreText.setString("Score: " + std::to_string(gameState.numEatenApples));
	window.draw(gameState.scoreText);
	gameState.gameOverText.setPosition(gameState.gameOverTextXCoordinate, gameState.gameOverTextYCoordinate);
	// window.draw(gameState.gameOverText);

	for (int i = 0; i < NUM_APPLES; ++i)
	{
		gameState.appleShape[i].setPosition(gameState.applePosition[i].x, gameState.applePosition[i].y);
		window.draw(gameState.appleShape[i]);
	}

	for (int i = 0; i < NUM_STONES; ++i)
	{
		gameState.stoneShape[i].setPosition(gameState.stonePosition[i].x, gameState.stonePosition[i].y);
		window.draw(gameState.stoneShape[i]);
	}
}

int main()
{
	// Init seed for random func
	int seed = (int)time(nullptr);
	srand(seed);

	// Init Window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game by DJEAKE <3");

	GameState gameState;
	InitGame(gameState);
	Player player;

	// Init game clock
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	// Main Loop
	while (window.isOpen())
	{
		// Calculate Time
		float currentTime = gameClock.getElapsedTime().asSeconds();
		gameState.deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Read events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		UpdateGame(gameState, gameState.deltaTime);
		window.clear();
		DrawGame(gameState,window);
		window.display();
	}
	return 0;
}
