// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float INITIAL_SPEED = 100.f;
const float PLAYER_SIZE = 20.f;
const float ACCELERATION = 20.f;
const int NUM_APPLES = 20;
const float APPLE_SIZE = 20.f;

int main()
{
	// Init seed for radom
	int seed = time(nullptr);
	srand(seed);

	// Init Window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game by DJEAKE <3");
	
	// Init player state
	float playerX = SCREEN_WIDTH / 2.f;
	float playerY = SCREEN_HEIGHT / 2.f;
	float playerSpeed = INITIAL_SPEED;
	int playerDirection = 0; // 0 - Right, 1 - Up, 2 - Left, 3 - down

	// Init player shape
	sf::RectangleShape playerShape;
	playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	playerShape.setFillColor(sf::Color::Red);
	playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
	playerShape.setPosition(playerX, playerY);

	// Init apple
	float applesX[NUM_APPLES];
	float applesY[NUM_APPLES];
	bool isAppleEaten[NUM_APPLES];
	sf::RectangleShape appleShape[NUM_APPLES];
	
	for (int i = 0; i < NUM_APPLES; ++i)
	{
		// Init apple state
		isAppleEaten[i] = false;
		applesX[i] = rand() / (float) RAND_MAX * SCREEN_WIDTH;
		applesY[i] = rand() / (float) RAND_MAX * SCREEN_HEIGHT;

		// Init apple shape
		appleShape[i].setSize(sf::Vector2f(APPLE_SIZE, APPLE_SIZE));
		appleShape[i].setFillColor(sf::Color::Green);
		appleShape[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
		appleShape[i].setPosition(applesX[i], applesY[i]);
	}

	// Init game clock
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

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
		{
			playerDirection = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			playerDirection = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			playerDirection = 2;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			playerDirection = 3;
		}

		playerSpeed += ACCELERATION * deltaTime;

		// Update player state
		if(playerDirection == 0)
		{
			playerX += playerSpeed * deltaTime;
		}
		else if (playerDirection == 1)
		{
			playerY -= playerSpeed * deltaTime;
		}
		else if (playerDirection == 2)
		{
			playerX -= playerSpeed * deltaTime;
		}
		else if (playerDirection == 3)
		{
			playerY += playerSpeed * deltaTime;
		}

		// Check screen borders
		if (playerX - PLAYER_SIZE / 2.f < 0.f || playerX + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
			playerY - PLAYER_SIZE / 2.f < 0.f || playerY + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
		{
			window.close();
			break;
		}


		window.clear();
		playerShape.setPosition(playerX, playerY);
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			if (!isAppleEaten[i])
			{
				window.draw(appleShape[i]);
			}
		}
		window.draw(playerShape);
		window.display();
	}

	return 0;
}
