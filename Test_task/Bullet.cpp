#include "Bullet.h"

Bullet::Bullet(
	const char* name,
	const float vellX, const float vellY,
	const float possX, const float possY, bool live
)
	:
	Animation(name), Object(possX, possY), isWork(live)
{
	velocity_x = vellX; velocity_y = vellY;
}

void Bullet::Update(int w, int h, float spec)
{
	const int out = 30;
	possition_x += velocity_x * (spec);
	possition_y += velocity_y * (spec);

	const int right = static_cast<int>(possition_x) + size_w;
	if (possition_x < out || right >= w)
	{
		FreeSprite();	isWork = false;
	}
	const int bottom = static_cast<int>(possition_y) + size_h;
	if (possition_y < out || bottom >= h)
	{
		FreeSprite();	isWork = false;
	}
}