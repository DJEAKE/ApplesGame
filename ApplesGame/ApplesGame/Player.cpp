#include "Player.h"
#include "Game.h"
namespace ApplesGame
{
	void InitPlayer(Player& player, const Game& game)
	{
		// Init player state
		player.playerPosition = { SCREEN_WIDTH / 2.f , SCREEN_HEIGHT / 2.f };
		player.playerSpeed = INITIAL_SPEED;
		player.playerDirection = PlayerDirection::Right;
		
		// Init player Sprite
		player.sprite.setTexture(game.playerTexture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(player.playerPosition.x, player.playerPosition.y);
		window.draw(player.sprite);
	}
}

