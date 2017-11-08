#include <random>
#include <time.h>
#include "Actions.h"
#include "GameState.h"
#include "Game.h"
#include "Player.h"
#include "Constants.h"



Player::~Player()
{
	return;
}


bool Player::drawSprite(ASGE::Renderer *renderer, int new_pos[])
{
	srand(time(NULL));

	sprite = nullptr;
	sprite = renderer->createRawSprite();
	sprite->dims[0] = 64;
	sprite->dims[1] = 64;

	new_pos[0] = 64;
	new_pos[1] = 64;

	sprite->position[0] = new_pos[0];
	sprite->position[1] = new_pos[1];


	if (sprite->loadTexture("..\\..\\Resources\\Textures\\player.png")) 
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


bool Player::collision(Pickup pickup, Body *snake_body, float &game_speed)
{
	//Check out of bounds
	if (sprite->position[0] > WINDOW_WIDTH-32 || sprite->position[0] < 0)
	{
		game_state = GameState::GAMEOVER;
		return false;
	}
	else if (sprite->position[1] > WINDOW_HEIGHT-32 || sprite->position[1] < 0)
	{
		game_state = GameState::GAMEOVER;
		return false;
	}

	//Check collision with pickups
	if (sprite->position[0] + 32 > pickup.pickup_sprite->position[0] - 32 && sprite->position[0] - 32 < pickup.pickup_sprite->position[0] + 32) //Check x position
	{
		if (sprite->position[1] + 32 >  pickup.pickup_sprite->position[1] - 32 && sprite->position[1] - 16 < pickup.pickup_sprite->position[1] + 32) //Check y position
		{
			score += 100;
			length ++;
			return true;
		}
	}

	//Check collisons with body
	for (int x = 0; x < length; x++)
	{
		if (sprite->position[0] + 32 > snake_body[x].sprite->position[0] - 32 && sprite->position[0] - 32 < snake_body[x].sprite->position[0] + 32) //Check x position
		{
			if (sprite->position[1] + 32 >  snake_body[x].sprite->position[1] - 32 && sprite->position[1] - 32 < snake_body[x].sprite->position[1] + 32) //Check y position
			{
				game_state = GameState::GAMEOVER;
				return false;
			}
		}
	}

	//Check collisions with duck nest
	if (sprite->position[0] >= int(WINDOW_WIDTH - 192) && sprite->position[1] >= int(WINDOW_HEIGHT - 128))
	{
		score += (100 * length)*float(length/2); //The more ducks the more points
		length = 0;
		game_speed = 30;
	}
	return false;
}

bool Player::reset()
{
	sprite->position[0] = 64;
	sprite->position[1] = 64;
	sprite->angle = 0.0f;
	length = 0;
	score = 0;
	movment_axis = 0;
	direction = 0;
	return true;
}