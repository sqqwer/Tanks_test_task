#include "Enemy.h"

Enemy::Enemy()
	:
	Animation(), Object(), alives(0), live(true)
{}

Enemy::Enemy(
	const char* name_ini, const char* bull_preset,
	int lives, int poss_x, int poss_y,
	void (*draw)(Sprite*, int, int)
)
	:
	Animation(name_ini, draw), bull_preset(bull_preset),
	Object(poss_x, poss_y), alives(lives)
{}

void Enemy::Shoot()
{
	WICH_SIDE(sd);
	ChioceOutShoot();
	bull.push_back(Bullet(
		bull_preset.c_str(),
		(sd == side::LEFT) ? -vellB : (sd == side::RIGHT) ? vellB : 0.0f,
		(sd == side::FRONT) ? -vellB : (sd == side::BOTTOM) ? vellB : 0.0f,
		out_x, out_y, true, drawSprite
	));
}

void Enemy::ChioceOutShoot()
{
	if (sd == side::FRONT)
	{
		out_x = possition_x + (size_w / 2) - 1;
		out_y = possition_y;
	}
	if (sd == side::LEFT)
	{
		out_y = possition_y + (size_h / 2) - 1;
		out_x = possition_x;
	}
	if (sd == side::RIGHT)
	{
		out_y = possition_y + (size_h / 2) - 1;
		out_x = possition_x + size_w;
	}
	if (sd == side::BOTTOM)
	{
		out_x = possition_x + (size_w / 2) - 1;
		out_y = possition_y + size_h;
	}
}

void Enemy::ClerBull(const unsigned int elem)
{
	bull.erase(bull.begin() + elem);
}

void Enemy::Draw()
{
	draw(
		Choice(velocity_x, velocity_y), GetX(), GetY()
	);
}

void Enemy::UpdateBullet(int screenX, int screenY, float mark)
{
	for (int i = 0; i < bull.size(); i++)
	{
		bull[i].Update(screenX, screenY, mark);
		if (!bull[i].Work())
			ClerBull(i);
	}
	if (bull.size())
	{
		for (int i = 0; i < bull.size(); i++)
			bull[i].Draw();
	}
	if (bull.capacity() && !bull.size())
	{
		bull.clear();
		std::vector<Bullet>().swap(bull);
	}
}