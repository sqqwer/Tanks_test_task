#include "Hero.h"
#include <iostream>

Hero::Hero()
	:
	Animation(), Object(), alives(0), live(true)
{}

Hero::Hero(
	const char* name_ini, unsigned int range,
	int lives, int poss_x, int poss_y
)
	:
	Animation(name_ini, range),
	Object(poss_x, poss_y), alives(lives)
{}
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