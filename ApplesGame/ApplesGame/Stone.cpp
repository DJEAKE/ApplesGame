#include "Stone.h"

namespace ApplesGame
{
	void InitStone(Stone& stone)
	{
		stone.stonePosition = GetRandomPositioInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

		stone.stoneShape.setSize(sf::Vector2f(STONE_SIZE, STONE_SIZE));
		stone.stoneShape.setFillColor(sf::Color::White);
		stone.stoneShape.setOrigin(STONE_SIZE / 2.f, STONE_SIZE / 2.f);
		stone.stoneShape.setPosition(stone.stonePosition.x, stone.stonePosition.y);
	}
}

