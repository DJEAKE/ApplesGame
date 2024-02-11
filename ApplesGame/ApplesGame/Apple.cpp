#include "Apple.h"
#include "Game.h"
#include <ctime>

namespace ApplesGame
{
	void InitApple(Apple& apple, const Game& game)
	{
		apple.sprite.setTexture(game.appleTexture);
		SetSpriteSize(apple.sprite, APPLE_SIZE, APPLE_SIZE);
		SetSpriteRelativeOriginOrigin(apple.sprite, 0.5f, 0.5f);
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		apple.sprite.setPosition(apple.applePosition.x, apple.applePosition.y);
		window.draw(apple.sprite);
	}

	void SetApplePosition(Apple& apple, const Position2D& position)
	{
		apple.applePosition = position;
	}

	Circle GetAppleCollider(const Apple& apple)
	{
		return {apple.applePosition, APPLE_SIZE / 2.f};
	}

	int SetRandomNumberApples()
	{
		srand(time(0));
		int randomNumberApples = rand() % (MAX_NUM_APPLES - MIN_NUM_APPLES + 1) + MIN_NUM_APPLES;
		return randomNumberApples;
	}
}

