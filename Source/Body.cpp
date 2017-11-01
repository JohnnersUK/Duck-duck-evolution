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

bool Body::drawSprite(ASGE::Renderer * renderer, int new_pos[])
{
	sprite = renderer->createRawSprite();
	sprite->dims[0] = 64;
	sprite->dims[1] = 64;
	sprite->position[0] = new_pos[0];
	sprite->position[1] = new_pos[1];


	if (sprite->loadTexture("..\\..\\Resources\\Textures\\Body.png"))
	{
		return true;
	}

	return false;
}


int Body::getPosition(int x)
{
	switch (x)
	{
	case 0: return sprite->position[0];
	case 1: return sprite->position[1];
	}
}


bool Body::reset()
{
	//TODO: Implement this
	return true;
}