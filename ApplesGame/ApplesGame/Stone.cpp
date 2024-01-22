#include "Stone.h"
#include "Game.h"

namespace ApplesGame
{
	void InitStone(Stone& stone, const Game& game)
	{
		stone.sprite.setTexture(game.stoneTexture);
		SetSpriteSize(stone.sprite, STONE_SIZE, STONE_SIZE);
		SetSpriteRelativeOriginOrigin(stone.sprite, 0.5f, 0.5f);
	}

	void DrawStone(Stone& stone, sf::RenderWindow& window)
	{
		stone.sprite.setPosition(stone.stonePosition.x, stone.stonePosition.y);
		window.draw(stone.sprite);
	}

	void SetStonePosition(Stone& stone, const Position2D& position)
	{
		stone.stonePosition = position;
	}

	Rectangle GetStoneCollider(const Stone& stone)
	{
		return { { stone.stonePosition.x - STONE_SIZE / 2.f, stone.stonePosition.y - STONE_SIZE / 2.f },
					{ STONE_SIZE, STONE_SIZE } };
	}
}

