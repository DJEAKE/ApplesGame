#include "Apple.h"

namespace ApplesGame
{
	void InitApple(Apple& apple)
	{
		apple.isAppleEaten = false;
		apple.applePosition = GetRandomPositioInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

		apple.appleShape.setRadius(APPLE_SIZE / 2.f);
		apple.appleShape.setFillColor(sf::Color::Green);
		apple.appleShape.setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
		apple.appleShape.setPosition(apple.applePosition.x, apple.applePosition.y);
	}
}

