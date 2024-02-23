#include <SFML/Graphics.hpp>
#include <cassert>
#include "GameMode.h"
#include "Game.h"

void ApplesGame::SetGameModeSetting(Game& game, sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && game.isGameFinished == false)
	{
		game.GameModeSettings |= GameModeSettingsInBitMask::PlayerAcceleration;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::F2) &&  !game.isGameFinished)
	{
		game.GameModeSettings &= ~GameModeSettingsInBitMask::PlayerAcceleration;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::F3) && !game.isGameFinished)
	{
		game.GameModeSettings |= GameModeSettingsInBitMask::InifiniteNumApples;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) || sf::Keyboard::isKeyPressed(sf::Keyboard::F4) && !game.isGameFinished)
	{
		game.GameModeSettings &= ~GameModeSettingsInBitMask::InifiniteNumApples;
		game.isInfiniteAppleCount = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !game.isGameFinished)
	{
		game.isSettingSelected = true;
	}
}

void ApplesGame::DrawGameSettingMenu(Game& game, sf::RenderWindow& window)
{
	sf::String string = R"(Settings:
		1 - with player acceleration;
		2 - without accelerating the player;
		3 - infinite apples;
		4 - a finite number of apples;
		enter - start the game.)";

	assert(game.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Bold.ttf"));
	if (!game.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Bold.ttf"))
	{
		game.background.setFillColor(sf::Color::Red);
	}
	sf::Text text;
	text.setFont(game.font);
	text.setString(string);
	text.setFillColor(sf::Color::Yellow);
	text.setCharacterSize(45);
	text.setPosition(SCREEN_HEIGHT/ 4, SCREEN_WIDTH / 4);

	window.draw(game.background);
	window.draw(text);
}

