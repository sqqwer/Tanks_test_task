#include "Block.h"

Block::Block()
{};

Block::Block(const char* name_ini, const float possX, const float possY, const int  type, bool triger)
	:
	Object(possX, possY), type(type)
{
	if (triger)
	{
		int w, h;
		unit.push_back(Animation(name_ini, drawSprite, possX, possY, true));
		getSpriteSize(unit[0].GetSprite(), w, h);
		unit.push_back(Animation(name_ini, drawSprite, possX + w, possY, true));
		unit.push_back(Animation(name_ini, drawSprite, possX, possY + h, true));
		unit.push_back(Animation(name_ini, drawSprite, possX + w, possY + h, true));
	}
	else
	{
		unit.push_back(Animation(name_ini, drawSprite, possX, possY, true));
	}
};

void Block::Draw()
{
	for (int i = 0; i < unit.size(); i++)
	{
		drawSprite(unit[i].GetSprite(), GetX(), GetY());
	}
};

void Block::ClearBlock()
{
	for (int i = 0; i < unit.size(); i++)
	{
		unit[i].Animation::FreeSprite();
		unit.erase(unit.begin() + i);
	}
	unit.clear(); unit.shrink_to_fit();
};

void Block::Draw(const float mark, const float animationMark)
{
	for (int i = 0; i < unit.size(); i++)
	{
		drawSprite(unit[i].DrawPresset(mark, animationMark), GetX(), GetY());
	}
};

void Block::DrawBrick()
{
	for (int i = 0; i < unit.size(); i++)
	{
		drawSprite(unit[i].GetSprite(), unit[i].GetAnimPosX(), unit[i].GetAnimPosY());
	}
};