#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Math.h" 

namespace ApplesGame
{
	Position2D GetRandomPositioInScreen(float screenWidth, float screenHeight)
	{
		Position2D result;
		result.x = rand() / (float)RAND_MAX * screenWidth;
		result.y = rand() / (float)RAND_MAX * screenHeight;
		return result;
	}

	bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Vector2D rect2Size)
	{
		float deltaX = (float)fabs(rect1Position.x - rect2Position.x);
		float deltaY = (float)fabs(rect1Position.y - rect2Position.y);
		return (deltaX <= (rect2Size.x + rect1Size.x) / 2.f && deltaY <= (rect2Size.y + rect1Size.y) / 2.f);
	}

	bool IsCircleCollide(Position2D circle1Position, float circle1Radius, Position2D circle2Position, float circle2Radius)
	{
		const auto distanceX = circle1Position.x - circle2Position.x;
		const auto distanceY = circle1Position.y - circle2Position.y;
		const auto squareDistance = distanceX * distanceX + distanceY * distanceY;
		float squareRadiusSum = (circle1Radius + circle2Radius) * (circle1Radius + circle2Radius) / 4;
		return (squareDistance <= squareRadiusSum);
	}
	
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}
	void SetSpriteRelativeOriginOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
	}
}

