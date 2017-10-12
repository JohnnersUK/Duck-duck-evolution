#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

#include "Actions.h"
#include "Constants.h"
#include "Game.h"
#include "GameFont.h"
#include "Player.h"

bool Player::drawPlayer(ASGE::Renderer *renderer)
{
	player_sprite = renderer->createRawSprite();

	player_sprite->position[0] = player_x;
	player_sprite->position[1] = player_y;

	if (player_sprite->loadTexture("..\\..\\Resources\\Textures\\player.png")) 
	{
		return true;
	}

}

Player::~Player()
{
	return;
}