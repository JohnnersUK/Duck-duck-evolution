#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

#include "Actions.h"
#include "Constants.h"
#include "Game.h"
#include "GameFont.h"
#include "Body.h"

Body::~Body()
{
	return;
}

bool Body::drawBody(ASGE::Renderer * renderer)
{
	body_sprite = renderer->createRawSprite();
	body_sprite->dims[0] = 64;
	body_sprite->dims[1] = 64;
	body_sprite->position[0] = 100;
	body_sprite->position[1] = 100;

	if (body_sprite->loadTexture("..\\..\\Resources\\Textures\\player.png"))
	{
		return true;
	}

	return false;
}
