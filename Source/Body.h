#pragma once
#include <Engine/Sprite.h>
#include "Snake.h"

class Body 
	: public Snake
{
public:
	//Functions
	Body() = default;
	~Body();

	bool drawSprite(ASGE::Renderer *renderer, int new_pos[]) override;
	bool reset() override;

	//Variables
	ASGE::Sprite* sprite;

	int getPosition(int x);
	int last_pos[1];
};
