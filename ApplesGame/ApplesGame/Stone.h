#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constans.h"

namespace ApplesGame
{
	struct Game;
	struct Stone
	{
		Position2D stonePosition;
		sf::Sprite sprite;
	};

	void InitStone(Stone& stone,  const Game& game);
	void DrawStone(Stone& stone, sf::RenderWindow& window);
	void SetStobePosition(Stone& stone, const Position2D& position);
	Rectangle GetStoneCollider(const Stone& stone);
}