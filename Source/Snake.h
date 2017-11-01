#pragma once
#include <Engine/Sprite.h>

class Snake
{
public:
	Snake() = default;
	~Snake() = default;

	virtual bool drawSprite(ASGE::Renderer *renderer, int new_pos[]) = 0;
	virtual bool reset() = 0;
};
