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

void Block::Draw()
{
	draw(GetSprite(), GetX(), GetY());
};