#include "Apple.h"
#include "Game.h"
namespace ApplesGame
{
	void InitApple(Apple& apple, const Game& game)
	{
		apple.isAppleEaten = false;
		apple.applePosition = GetRandomPositioInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

		apple.sprite.setTexture(game.appleTexture);
		SetSpriteSize(apple.sprite, APPLE_SIZE, APPLE_SIZE);
		SetSpriteRelativeOriginOrigin(apple.sprite, 0.5f, 0.5f);
	}
	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		apple.sprite.setPosition(apple.applePosition.x, apple.applePosition.y);
		window.draw(apple.sprite);
	}
}

