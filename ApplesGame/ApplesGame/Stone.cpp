#include "Stone.h"
#include "Game.h"

namespace ApplesGame
{
	// Implementation of stone initialization
	void InitStone(Stone& stone, const Game& game)
	{
		stone.sprite.setTexture(game.stoneTexture);
		SetSpriteSize(stone.sprite, STONE_SIZE, STONE_SIZE);
		SetSpriteRelativeOriginOrigin(stone.sprite, 0.5f, 0.5f);
	}

	// Implementation of stone rendering
	void DrawStone(Stone& stone, sf::RenderWindow& window)
	{
		stone.sprite.setPosition(stone.stonePosition.x, stone.stonePosition.y);
		window.draw(stone.sprite);
	}

	// Implementation of stone position setting
	void SetStonePosition(Stone& stone, const Position2D& position)
	{
		stone.stonePosition = position;
	}

	// Implementation of getting an stone collider
	Rectangle GetStoneCollider(const Stone& stone)
	{
		return { { stone.stonePosition.x - STONE_SIZE / 2.f, stone.stonePosition.y - STONE_SIZE / 2.f },
					{ STONE_SIZE, STONE_SIZE } };
	}
}

