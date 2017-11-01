#include <Engine/Sprite.h>
#include "Bullet.h"

bool Bullet::drawBullet(ASGE::Renderer* renderer)
{
	//bullet_sprite = renderer->createRawSprite();
	bullet_sprite->dims[0] = 64;
	bullet_sprite->dims[1] = 64;


	if (bullet_sprite->loadTexture("..\\..\\Resources\\Textures\\Bullet.png"))
	{
		return true;
	}
	return false;
}
