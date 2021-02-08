#include "Hero.h"
#include <iostream>

Hero::Hero()
	:
	Animation(), Object(), alives(0), live(true)
{};

Hero::Hero(
	const char* name_ini, const char* bull_preset,
	int lives, const float poss_x, const float poss_y,
	void (*draw)(Sprite*, int, int)
)
	:
	Animation(name_ini, draw), bull_preset(bull_preset),
	Object(poss_x, poss_y), alives(lives)
{};
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
};

void Hero::ReleasedKey()
{
	velocity_x = 0;
	velocity_y = 0;
};

void Hero::Shoot()
{
	WICH_SIDE(sd);
	ChioceOutShoot();
	bull.push_back(Bullet(
		bull_preset.c_str(),
		(sd == side::LEFT) ? -vellB : (sd == side::RIGHT) ? vellB : 0.0f,
		(sd == side::FRONT) ? -vellB : (sd == side::BOTTOM) ? vellB : 0.0f,
		out_x, out_y, true, drawSprite
	));
};

void Hero::ChioceOutShoot()
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
};

void Hero::ClerBull(const unsigned int elem)
{
	bull.erase(bull.begin() + elem);
};

void Hero::Draw()
{
	draw(
		Choice(velocity_x, velocity_y), GetX(), GetY()
	);
};

void Hero::UpdateBullet(
	int screenX, int screenY, float mark,
	std::vector<Enemy>& en
)
{
	for (int i = 0; i < bull.size(); i++)
	{
		bull[i].Update(screenX, screenY, mark);
		if (bull[i].Work()) for (int j = 0; j < en.size(); j++) if (en[j].isAlive())
		{
			if (bull[i].GetX() + bull[i].GetSpW() <=
				en[j].GetX() + en[j].GetSpW() &&
				bull[i].GetX() >= en[j].GetX())
			{
				if (bull[i].GetY() + bull[i].GetSpH() <=
					en[j].GetY() + en[j].GetSpH() &&
					bull[i].GetY() >= en[j].GetY())
				{
					bull[i].SetWork(false);
					en[j].SetLive(false);
					en[j].SetVellY(0.0f);
					en[j].SetVellX(0.0f);
					if (!en[i].bull.size())
						en.erase(en.begin() + j);
				}
			}
		}
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
};