#pragma once
#include <Engine/Sprite.h>

class Player
{
public:
	ASGE::Sprite* player_sprite;
	int player_direction = 0;
	int player_speed = 0; //The player current speed (Do not modify)
	int player_speed_multi = 5; //Change this to modify the players speed

	Player() = default;
	~Player();
	bool drawPlayer(ASGE::Renderer *rendere);

private:
	int player_x = 100;
	int player_y = 100;
};
