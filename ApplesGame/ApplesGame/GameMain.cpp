// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float INITIAL_SPEED = 0.1f;
const float PLAYER_SIZE = 20.f;

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game by DJEAKE <3");
	float playerX = SCREEN_WIDTH / 2.f;
	float playerY = SCREEN_HEIGHT / 2.f;
	float playerSpeed = INITIAL_SPEED;
	int playerDirection = 0; // 0 - Right, 1 - Up, 2 - Left, 3 - down

	sf::RectangleShape playerShape;
	playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	playerShape.setFillColor(sf::Color::Red);
	playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
	playerShape.setPosition(playerX, playerY);

	while (window.isOpen())
	{
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

		// Update player state
		if(playerDirection == 0)
		{
			playerX += playerSpeed;
		}
		else if (playerDirection == 1)
		{
			playerY -= playerSpeed;
		}
		else if (playerDirection == 2)
		{
			playerX -= playerSpeed;
		}
		else if (playerDirection == 3)
		{
			playerY += playerSpeed;
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
		window.draw(playerShape);
		window.display();
	}

	return 0;
}
