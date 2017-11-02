#pragma once
#include "Snake.h"
#include "Body.h"
#include "Pickup.h"
#include <Engine/Sprite.h>

class Player
	: public Snake
{
public:
	Player() = default;
	~Player();

	ASGE::Sprite* sprite;
	int movment_axis = 0; //Which axis the player is currently moving along
	int direction = 0; //The players current direction (Do not modify)

	int getLength();
	int getScore();

	bool drawSprite(ASGE::Renderer *renderer, int new_pos[]) override;
	bool collision(Pickup pickup, Body *snake_body[]);
	bool reset() override;


private:
	int length = 0;
	int score = 0;
	int ammo = 5;
};
