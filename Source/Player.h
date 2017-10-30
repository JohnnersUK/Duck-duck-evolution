#pragma once
#include <Engine/Sprite.h>
#include "Body.h"
#include "Pickup.h"

class Player
{
public:
	ASGE::Sprite* player_sprite;
	int movment_axis = 0; //Which axis the player is currently moving along
	int direction = 0; //The players current direction (Do not modify)


	Player() = default;
	~Player();
	int getLength();
	int getScore();
	bool drawPlayer(ASGE::Renderer *rendere);
	bool collision(Pickup pickup, Body *snake_body[]);
	bool reset();

private:
	int x_position = 100;
	int y_position = 100;
	int length = 0;
	int score = 0;
};
