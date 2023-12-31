#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constans.h"

namespace ApplesGame
{
	struct Stone
	{
		Position2D stonePosition;
		sf::RectangleShape stoneShape;
	};

	void InitStone(Stone& stone);
}