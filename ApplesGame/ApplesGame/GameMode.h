#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	struct Game;

	enum GameModeSettingsInBitMask
	{
		PlayerAcceleration = 1 << 0,
		InifiniteNumApples = 1 << 1
	};

	void SetGameModeSetting(Game& game, sf::RenderWindow& window);
	void DrawGameSettingMenu(Game& game, sf::RenderWindow& window);
}