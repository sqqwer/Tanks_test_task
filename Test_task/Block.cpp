#include "Block.h"

Block::Block()
{};

Block::Block(
	const char* name_ini,
	const float possX, const float possY,
	void (*draw)(Sprite*, int, int), const int  type
)
	:
	Animation(name_ini, draw), Object(possX, possY), type(type)
{};

void Block::Draw()
{
	draw(GetWallPoss(), GetX(), GetY());
};

void Block::Draw(float& mark)
{
	draw(DrawPresset(mark), GetX(), GetY());
};