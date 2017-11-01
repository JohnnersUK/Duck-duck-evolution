#pragma once
#include <Engine/Sprite.h>
#include "Player.h"

class Body
{
public:
	ASGE::Sprite* body_sprite;

	Body() = default;
	~Body();

	bool drawBody(ASGE::Renderer *renderer, int new_pos[]);
	int getPosition(int x);
	int last_pos[1];
};
