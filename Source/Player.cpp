#include <random>
#include <time.h>
#include "Actions.h"
#include "GameState.h"
#include "Game.h"
#include "Player.h"



Player::~Player()
{
	return;
}


bool Player::drawPlayer(ASGE::Renderer *renderer)
{
	srand(time(NULL));
	player_sprite = nullptr;
	player_sprite = renderer->createRawSprite();
	player_sprite->dims[0] = 64;
	player_sprite->dims[1] = 64;
	player_sprite->position[0] = x_position;
	player_sprite->position[1] = y_position;

	if (player_sprite->loadTexture("..\\..\\Resources\\Textures\\player.png")) 
	{
		return true;
	}
	return false;
}

int Player::getLength()
{
	return length;
}

int Player::getScore()
{
	return score;
}

bool Player::collision(Pickup pickup, Body *snake_body[])
{
	//Check out of bounds
	if (player_sprite->position[0] > 1280 || player_sprite->position[0] < 0)
	{
		game_state = GameState::GAMEOVER;
		return false;
	}
	if (player_sprite->position[1] > 720 || player_sprite->position[1] < 0)
	{
		game_state = GameState::GAMEOVER;
		return false;
	}

	//Check collision with pickups
	if (player_sprite->position[0] + 32 > pickup.pickup_sprite->position[0] - 32 && player_sprite->position[0] - 32 < pickup.pickup_sprite->position[0] + 32) //Check x position
	{
		if (player_sprite->position[1] + 32 >  pickup.pickup_sprite->position[1] - 32 && player_sprite->position[1] - 32 < pickup.pickup_sprite->position[1] + 32) //Check y position
		{
			score += 100;
			ammo = 5;
			length ++;
			snake_body[int(length - 1)] = new Body;
			pickup.pickup_sprite->position[0] = rand() % 1216;
			pickup.pickup_sprite->position[1] = rand() % 656;
			return true;
		}
	}

	//Check collisons with body
	for (int x = 0; x < length; x++)
	{
		if (player_sprite->position[0] + 32 > snake_body[x]->body_sprite->position[0] - 32 && player_sprite->position[0] - 32 < snake_body[x]->body_sprite->position[0] + 32) //Check x position
		{
			if (player_sprite->position[1] + 32 >  snake_body[x]->body_sprite->position[1] - 32 && player_sprite->position[1] - 32 < snake_body[x]->body_sprite->position[1] + 32) //Check y position
			{
				game_state = GameState::GAMEOVER;
				return false;
			}
		}
	}

	return false;
}

bool Player::reset()
{
	player_sprite->position[0] = 100;
	player_sprite->position[1] = 100;
	player_sprite->angle = 0.0f;
	x_position = 100;
	y_position = 100;
	length = 0;
	score = 100;
	movment_axis = 0;
	direction = 0;
	return true;
}