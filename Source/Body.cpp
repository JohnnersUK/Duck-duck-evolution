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

bool Body::drawBody(ASGE::Renderer * renderer, int new_pos[])
{
	body_sprite = renderer->createRawSprite();
	body_sprite->dims[0] = 64;
	body_sprite->dims[1] = 64;
	body_sprite->position[0] = new_pos[0];
	body_sprite->position[1] = new_pos[1];


	if (body_sprite->loadTexture("..\\..\\Resources\\Textures\\Body.png"))
	{
		return true;
	}

	return false;
}

int Body::getPosition(int x)
{
	switch (x)
	{
	case 0: return body_sprite->position[0];
	case 1: return body_sprite->position[1];
	}

			
}