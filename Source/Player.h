#pragma once
#include <Engine/Sprite.h>
#include "Body.h"
#include "Pickup.h"

class Player
{
public:
	ASGE::Sprite* player_sprite;
	int player_axis = 0; //Which axis the player is currently moving along
	int player_direction = 0; //The players current direction (Do not modify)


	Player() = default;
	~Player();
	int getLength();
	int getScore();
	bool drawPlayer(ASGE::Renderer *rendere);
	bool collision(Pickup pickup, Body *snake_body[]);

private:
	int player_x = 100;
	int player_y = 100;
	int length = 0;
	int score = 0;
};
