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
	player_sprite->dims[0] = 64;
	player_sprite->dims[1] = 64;
	player_sprite->position[0] = player_x;
	player_sprite->position[1] = player_y;

	if (player_sprite->loadTexture("..\\..\\Resources\\Textures\\player.png")) 
	{
		return true;
	}
	return false;
}

Player::~Player()
{
	return;
}

int Player::getLength()
{
	return length;
}

bool Player::collision(Pickup pickup, Body *snake_body[])
{
	if (player_sprite->position[0] + 32 > pickup.pickup_sprite->position[0] - 32 && player_sprite->position[0] - 32 < pickup.pickup_sprite->position[0] + 32) //Check x position
	{
		if (player_sprite->position[1] + 32 >  pickup.pickup_sprite->position[1] - 32 && player_sprite->position[1] - 32 < pickup.pickup_sprite->position[1] + 32) //Check y position
		{
			length += 1;
			snake_body[length - 1] = new Body;
			pickup.pickup_sprite->position[0] += 50;
			pickup.pickup_sprite->position[1] += 10;
			return true;
		}
	}
	return false;
}