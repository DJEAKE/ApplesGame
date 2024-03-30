#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	// �����. ���� ������� � �����.����� ����� �������
	// ������� �������� 1 ��� ��� �������������
	// ����� ����� ������� ������� ����� ����� ������
	// ������ ������ �� ������� ����������� ����� ������ ������
	struct Game;

	void GenerateScoreTable(Game& game, sf::RenderWindow& window);
	void UpdateScoreTable(Game& game, sf::RenderWindow& window);
	void DrawScoreTable(Game& game, sf::RenderWindow& window);

}