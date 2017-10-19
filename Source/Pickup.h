#pragma once
#pragma once
#include <Engine/Sprite.h>

class Pickup
{
public:
	ASGE::Sprite* pickup_sprite;

	Pickup() = default;
	~Pickup() = default;

	bool drawPickup(ASGE::Renderer *rendere);
};
