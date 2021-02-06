#include <iostream>

#include "Hero.h"

Hero::Hero()
	:
	Object(), lives(0), live(true)
{}

Hero::Hero(int lives, int poss_x, int poss_y)
	:
	Object(poss_x, poss_y), lives(lives)
{
	object[0] = createSprite("tank1.tga");
	object[1] = createSprite("tank2.tga");
}

bool Hero::isAlive() const {
	return live;
}

void Hero::SetLast(const FRKey k)
{
	last = k;
}

// Function update possiition of object
void Hero::PressKey(FRKey k)
{
	const float speed = 100.0f;
	if (k == FRKey::RIGHT)
	{
		velocity_x = speed;
		velocity_y = 0.0f;
	}
	if (k == FRKey::LEFT)
	{
		velocity_x = -speed;
		velocity_y = 0.0f;
	}
	if (k == FRKey::DOWN)
	{
		velocity_y = speed;
		velocity_x = 0.0f;
	}
	if (k == FRKey::UP)
	{
		velocity_y = -speed;
		velocity_x = 0.0f;
	}
}

void Hero::ReleasedKey()
{
	velocity_x = 0;
	velocity_y = 0;
}

void Hero::Update(int w, int h, float spec)
{
	possition_x += velocity_x * (spec);
	possition_y += velocity_y * (spec);
	const int right = (int)possition_x + size_w;
	if (possition_x  < 0)
	{
		possition_x = 0;
	}
	else if (right >= w)
	{
		possition_x = w - size_w;
	}
	const int bottom = (int)possition_y + size_h;
	if (possition_y < 0)
	{
		possition_y = 0;
	}
	else if (bottom >= h)
	{
		possition_y = h - size_h;
	}
}
