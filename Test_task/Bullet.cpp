#include "Bullet.h"

Bullet::Bullet()
{};

Bullet::Bullet(
	const char* name,
	const float vellX, const float vellY,
	const float possX, const float possY, bool live,
	void (*draw)(Sprite*, int, int),
	const int outOfScreenX, const int outOfScreenY
)
	:
	Animation(name, draw), isWork(live),
	Object(possX, possY, outOfScreenX, outOfScreenY)
{
	velocity_x = vellX; velocity_y = vellY;
};

void Bullet::Update(int w, int h, float spec,
	const int outOfScreenX, const int outOfScreenY
)
{
	possition_x += velocity_x * (spec);
	possition_y += velocity_y * (spec);

	const int right = (int)possition_x + size_w;
	if (possition_x < outOfScreenX || right >= w)
	{
		FreeSprite();	isWork = false;
	}
	const int bottom = (int)(possition_y) + size_h;
	if (possition_y < outOfScreenY || bottom >= h)
	{
		FreeSprite();	isWork = false;
	}
};

void Bullet::Draw()
{
	draw(
		Choice(velocity_x, velocity_y), GetX(), GetY()
	);
};