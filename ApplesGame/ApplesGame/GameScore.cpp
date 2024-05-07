#include <SFML/Graphics.hpp>
#include <string>
#include "GameScore.h"
#include "Game.h"
namespace ApplesGame
{
	void GenerateScoreTable(Game& game)
	{
		// Generate fake records table
		game.recordsTable =
		{
			{"John", MAX_NUM_APPLES / 2},
			{"Jane", MAX_NUM_APPLES / 3 },
			{"Alice", MAX_NUM_APPLES / 4 },
			{"Bob", MAX_NUM_APPLES / 5 },
			{"Clementine", MAX_NUM_APPLES / 6 },
            {"Player", game.numEatenApples},
		};
	}

	void UpdateScoreTable(Game& game)
	{
        // Find the "Player" entry
        auto playerIt = game.recordsTable.find("Player");
        playerIt->second = game.numEatenApples;
	}

	void DrawScoreTable(Game& game, sf::RenderWindow& window)
	{
        // ����� ��� ������
        sf::Font font;
        if (!font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Bold.ttf")) // �������� �� ���� � ������ ������
        {
            return; // ������ �������� ������
        }

        // ��������� ������
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);

        // ������� ��� ������
        float yPos = 100; // ��������� ������� �� Y

        // ����� ������ ������ � �������
        for (const auto& record : game.recordsTable)
        {
            std::string recordText = record.first + ": " + std::to_string(record.second);
            text.setString(recordText);
            text.setPosition(100, yPos); // ������� ������
            window.draw(text);
            yPos += 30; // ����� ���� ��� ��������� ������
        }
	}
}

