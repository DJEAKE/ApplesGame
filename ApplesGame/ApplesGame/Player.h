#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constans.h"

namespace ApplesGame
{
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
		sf::Sprite sprite;
		float playerSpeed = INITIAL_SPEED;
	};

	struct Game;

	void InitPlayer(Player& player, const Game&);

	void DrawPlayer(Player& player, sf::RenderWindow& window);

}
