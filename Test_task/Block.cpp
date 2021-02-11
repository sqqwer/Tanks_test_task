#include "Block.h"

Block::Block()
{};

Block::Block(
	const char* name_ini,
	const float possX, const float possY,
	void (*draw)(Sprite*, int, int)
)
	:
	Animation(name_ini, draw), Object(possX, possY)
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

void Block::ClearBlock()
{
	Animation::FreeSprite();
};

void Block::Draw(const float mark, const float animationMark)
{
	draw(DrawPresset(mark, animationMark), GetX(), GetY());
};

void Block::DrawBrick()
{
	draw(GetWallPoss(), GetX(), GetY());
};