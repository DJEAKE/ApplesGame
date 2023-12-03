#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constans.h"

struct Apple
{
	// Apples data
	Position2D applePosition;
	sf::CircleShape appleShape;
	bool isAppleEaten = false;
};

void InitApple(Apple& apple);;