#pragma once
#include <Engine/Sprite.h>

class Bullet
{
public:
	Bullet() = default;
	~Bullet() = default;

	ASGE::Sprite* bullet_sprite;
	int movment_axis;
	int direction;
	
	bool drawBullet(ASGE::Renderer* renderer);

private:
	int speed;

};
