#pragma once
#include <Engine/Sprite.h>

class Bat
{
public:
	Bat() = default;
	~Bat() = default;

	ASGE::Sprite* bat_sprite;

	bool drawSprite(ASGE::Renderer* renderer);

private:


};
