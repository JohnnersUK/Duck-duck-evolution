#pragma once
#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

#include "Actions.h"
#include "Constants.h"
#include "Game.h"
#include "GameFont.h"

class Player
{
public:
	ASGE::Sprite* player_sprite;
	int player_direction = 0;
	int player_speed = 0;

	Player() = default;
	~Player();
	bool drawPlayer(ASGE::Renderer *rendere);

private:
	int player_x = 100;
	int player_y = 100;

};
