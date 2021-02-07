#include "Hero.h"
#include <iostream>

Hero::Hero()
	:
	Object(), lives(0), live(true)
{}

Hero::Hero(const char* name_ini, unsigned int range, int lives, int poss_x, int poss_y)
	:
	Animation(name_ini, range), Object(poss_x, poss_y), lives(lives)
{}

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
	const float speed = 70.0f;
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
// Update possition
void Hero::Update(int w, int h, float spec)
{
	const int out = 50;
	possition_x += velocity_x *(spec);
	possition_y += velocity_y *(spec);
	const int right = (int)possition_x + size_w;
	if (possition_x  < out)
	{
		possition_x = (float)out;
	}
	else if (right >= w)
	{
		possition_x = w - size_w;
	}
	const int bottom = (int)possition_y + size_h;
	if (possition_y < out)
	{
		possition_y = (float)out;
	}
	else if (bottom >= h)
	{
		possition_y = h - size_h;
	}
}
// Animation
