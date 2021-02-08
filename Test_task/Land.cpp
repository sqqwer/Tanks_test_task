#include "Land.h"

Land::Land()
{};

Land::Land(const char* name, void (*draw)(Sprite*, int, int))
	:
	Animation(name, draw), Object(30.0f, 30.0f)
{};

void Land::Draw()
{
	draw(GetSprite(), GetX(), GetY());
};
