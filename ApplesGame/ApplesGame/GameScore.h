#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	// Огран. имен игроков и огран.числа очков игроков
	// Таблица генерица 1 раз при инициализации
	// игрок может открыть таблицу после своей смерти
	// данные игрока из таблицы обновляются после смерти игрока
	struct Game;

	void GenerateScoreTable(Game& game, sf::RenderWindow& window);
	void UpdateScoreTable(Game& game, sf::RenderWindow& window);
	void DrawScoreTable(Game& game, sf::RenderWindow& window);

}