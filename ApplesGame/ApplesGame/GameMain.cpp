// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int NUM_APPLES = 15;
const int NUM_STONES = 3;
const float PLAYER_SIZE = 20.f;
const float APPLE_SIZE = 20.f;
const float STONE_SIZE = 20.f;
const float INITIAL_SPEED = 100.f;
const float ACCELERATION = 15.5f;

int main()
{
	// Init seed for random func
	int seed = (int)time(nullptr);
	srand(seed);

	// Init game clock
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	// Init eaten apple counter.
	int numEatenApples = 0;

	// Init Window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game by DJEAKE <3");

	// Init player state
	float playerXCoordinate = SCREEN_WIDTH / 2.f;
	float playerYCoordinate = SCREEN_HEIGHT / 2.f;
	float playerSpeed = INITIAL_SPEED;
	int playerDirection = 0; // 0 - Right, 1 - Up, 2 - Left, 3 - down

	// Init player shape
	sf::RectangleShape playerShape;
	playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	playerShape.setFillColor(sf::Color::Red);
	playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
	playerShape.setPosition(playerXCoordinate, playerYCoordinate);

	// Declare apples
	float applesXCoordinate[NUM_APPLES];
	float applesYCoordinate[NUM_APPLES];
	bool isAppleEaten[NUM_APPLES];
	sf::CircleShape appleShape[NUM_APPLES];

	// Init apple state & init apple shape
	for (int i = 0; i < NUM_APPLES; ++i)
	{
		// Apple State
		isAppleEaten[i] = false;
		applesXCoordinate[i] = rand() / (float)RAND_MAX * SCREEN_WIDTH;
		applesYCoordinate[i] = rand() / (float)RAND_MAX * SCREEN_HEIGHT;

		// Apple shape
		appleShape[i].setRadius(APPLE_SIZE / 2.f);
		appleShape[i].setFillColor(sf::Color::Green);
		appleShape[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
		appleShape[i].setPosition(applesXCoordinate[i], applesYCoordinate[i]);
	}

	// Declare stone
	float stoneXCoordinate[NUM_STONES];
	float stoneYCoordinate[NUM_STONES];
	sf::RectangleShape stoneShape[NUM_STONES];

	// Init stone state & init stone shape
	for (int i = 0; i < NUM_STONES; ++i)
	{
		// stone State
		stoneXCoordinate[i] = rand() / (float)RAND_MAX * SCREEN_WIDTH;
		stoneYCoordinate[i] = rand() / (float)RAND_MAX * SCREEN_HEIGHT;

		// stone shape
		stoneShape[i].setSize(sf::Vector2f(STONE_SIZE, STONE_SIZE));
		stoneShape[i].setFillColor(sf::Color::White);
		stoneShape[i].setOrigin(STONE_SIZE / 2.f, STONE_SIZE / 2.f);
		stoneShape[i].setPosition(stoneXCoordinate[i], stoneYCoordinate[i]);
	}

	// Declare & init score text ui 
	sf::Text scoreText;
	sf::Font font;
	font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Bold.ttf");
	float scoreTextXCoordinate = 2.5f;
	float scoreTextYCoordinate = 2.5f;
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::Yellow);
	scoreText.setString("Score: ");
	scoreText.setPosition(scoreTextXCoordinate, scoreTextYCoordinate);

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
			playerDirection = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			// 1 - Up
			playerDirection = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// 2 - Left
			playerDirection = 2;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			// 3 - down
			playerDirection = 3;
		}

		// Update player state
		if (playerDirection == 0)
		{
			playerXCoordinate += playerSpeed * deltaTime;
		}
		else if (playerDirection == 1)
		{
			playerYCoordinate -= playerSpeed * deltaTime;
		}
		else if (playerDirection == 2)
		{
			playerXCoordinate -= playerSpeed * deltaTime;
		}
		else if (playerDirection == 3)
		{
			playerYCoordinate += playerSpeed * deltaTime;
		}

		// Check screen borders
		if (playerXCoordinate - PLAYER_SIZE / 2.f < 0.f || playerXCoordinate + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
			playerYCoordinate - PLAYER_SIZE / 2.f < 0.f || playerYCoordinate + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
		{

		}

		// Check apple colliders
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			if (!isAppleEaten[i])
			{

				float squareDistance = (playerXCoordinate - applesXCoordinate[i]) * (playerXCoordinate - applesXCoordinate[i]) +
					(playerYCoordinate - applesYCoordinate[i]) * (playerYCoordinate - applesYCoordinate[i]);
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
			float deltaX = fabs(playerXCoordinate - stoneXCoordinate[i]);
			float deltaY = fabs(playerYCoordinate - stoneYCoordinate[i]);

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
		playerShape.setPosition(playerXCoordinate, playerYCoordinate);

		for (int i = 0; i < NUM_APPLES; ++i)
		{
			if (!isAppleEaten[i])
			{
				window.draw(appleShape[i]);
			}
			else {
				// Init apple state
				isAppleEaten[i] = false;
				applesXCoordinate[i] = rand() / (float)RAND_MAX * SCREEN_WIDTH;
				applesYCoordinate[i] = rand() / (float)RAND_MAX * SCREEN_HEIGHT;

				// Init apple shape
				appleShape[i].setRadius(APPLE_SIZE / 2.f);
				appleShape[i].setFillColor(sf::Color::Green);
				appleShape[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
				appleShape[i].setPosition(applesXCoordinate[i], applesYCoordinate[i]);
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
