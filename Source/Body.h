#pragma once

#pragma once
#include <Engine/Sprite.h>

class Body
{
public:
	ASGE::Sprite* body_sprite;

	Body() = default;
	~Body();

	bool drawBody(ASGE::Renderer *renderer);
	int getPosition(int x);

};
