#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constans.h"

namespace ApplesGame 
{
	struct Game;
	struct Apple
	{
		Position2D applePosition;
		sf::Sprite sprite;
		int numApples;
		Apple(int num) : numApples(num) {}
	};

	void InitApple(Apple& apple, const Game& game);
	void DrawApple(Apple& applle, sf::RenderWindow& window);
	void SetApplePosition(Apple& apple, const Position2D& position);
	Circle GetAppleCollider(const Apple& apple);
	int SetRandomNumberApples();
}
