#include "Player.h"

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
