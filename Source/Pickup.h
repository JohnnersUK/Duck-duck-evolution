#pragma once
#include <Engine/Sprite.h>
#include "Player.h"
#include "Body.h"

class Pickup
{
public:
	//Functions
	Pickup() = default;
	~Pickup() = default;

	bool drawPickup(ASGE::Renderer *rendere);
	bool reset();

	//Variables
	ASGE::Sprite* pickup_sprite;
};
