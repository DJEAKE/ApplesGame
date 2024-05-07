#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	// Огран. имен игроков и огран.числа очков игроков
	// Таблица генерица 1 раз при инициализации
	// игрок может открыть таблицу после своей смерти
	// данные игрока из таблицы обновляются после смерти игрока
	struct Game;

	void GenerateScoreTable(Game& game);
	void UpdateScoreTable(Game& game);
	void DrawScoreTable(Game& game, sf::RenderWindow& window);

}