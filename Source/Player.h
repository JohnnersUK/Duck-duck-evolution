#pragma once
#include <Engine/Sprite.h>
#include "Body.h"
#include "Pickup.h"
#include "Bullet.h"

class Player
{
public:
	Player() = default;
	~Player();

	ASGE::Sprite* player_sprite;
	int movment_axis = 0; //Which axis the player is currently moving along
	int direction = 0; //The players current direction (Do not modify)

	int getLength();
	int getScore();

	bool drawPlayer(ASGE::Renderer *rendere);
	bool collision(Pickup pickup, Body *snake_body[]);
	bool reset();

	Bullet bullet[4];

private:
	int length = 0;
	int score = 0;
	int ammo = 5;
};
