#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constans.h"

enum class PlayerDirection : int
{
	Right = 0,
	Up,
	Left,
	Down
};

struct Player
{
	// Player data
	Position2D playerPosition;
	PlayerDirection playerDirection = PlayerDirection::Right;;
	sf::RectangleShape playerShape;
	float playerSpeed = INITIAL_SPEED;
};

void InitPlayer(Player& player);;