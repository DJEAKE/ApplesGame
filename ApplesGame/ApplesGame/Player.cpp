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
		SetSpriteRelativeOriginOrigin(player.sprite, 0.5f, 0.5f);
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(player.playerPosition.x, player.playerPosition.y);
		window.draw(player.sprite);

		if (player.playerDirection == PlayerDirection::Left)
		{
			SetSpriteSize(player.sprite, -PLAYER_SIZE, PLAYER_SIZE);
			player.sprite.setRotation(0.f);
		}
		else
		{
			SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
			player.sprite.setRotation((float)player.playerDirection * -90.f);
		}
	}
}

