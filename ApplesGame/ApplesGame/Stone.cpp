#include "Stone.h"
#include "Game.h"
namespace ApplesGame
{
	void InitStone(Stone& stone, const Game& game)
	{
		stone.stonePosition = GetRandomPositioInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

		stone.sprite.setTexture(game.stoneTexture);
		SetSpriteSize(stone.sprite, STONE_SIZE, STONE_SIZE);
		SetSpriteRelativeOriginOrigin(stone.sprite, 0.5f, 0.5f);
	}
	void DrawStone(Stone& stone, sf::RenderWindow& window)
	{
		stone.sprite.setPosition(stone.stonePosition.x, stone.stonePosition.y);
		window.draw(stone.sprite);
	}
}

