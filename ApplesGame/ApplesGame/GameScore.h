#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	// �����. ���� ������� � �����.����� ����� �������
	// ������� �������� 1 ��� ��� �������������
	// ����� ����� ������� ������� ����� ����� ������
	// ������ ������ �� ������� ����������� ����� ������ ������
	struct Game;

	void GenerateScoreTable(Game& game);
	void UpdateScoreTable(Game& game);
	void DrawScoreTable(Game& game, sf::RenderWindow& window);

}