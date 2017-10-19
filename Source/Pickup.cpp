#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

#include "Actions.h"
#include "Constants.h"
#include "Game.h"
#include "GameFont.h"
#include "Pickup.h"


bool Pickup::drawPickup(ASGE::Renderer* renderer)
{
	pickup_sprite = renderer->createRawSprite();
	pickup_sprite->dims[0] = 64;
	pickup_sprite->dims[1] = 64;
	pickup_sprite->position[0] = 400;
	pickup_sprite->position[1] = 400;

	if (pickup_sprite->loadTexture("..\\..\\Resources\\Textures\\player.png"))
	{
		return true;
	}
	
	return false;
}
