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
}
void Hero::TankColisium(Enemy& en, const float mark)
{
	if (
		possition_x + size_w >= en.GetX() &&
		possition_x <= en.GetX() + en.GetSpW()
		)
	{
		if (
			possition_y + size_h >= en.GetY() &&
			possition_y <= en.GetY() + en.GetSpH()
			)
		{
			en.BackX(en.GetvellX(), mark);
			en.BackY(en.GetvellY(), mark);
			en.SetVellX(0.0f);
			en.SetVellY(0.0f);


			if (!velocity_y)
			{
				BackX(velocity_x, mark);
			}
			else if (!velocity_x)
			{
				BackY(velocity_y, mark);
			}
		}
	}
};

void Hero::ReleasedKey()
{
	velocity_x = 0;
	velocity_y = 0;
};

void Hero::Shoot()
{
	sd = (side)ShootSide();
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
	bull[elem].FreeSprite(); bull.erase(bull.begin() + elem);
};

void Hero::Draw()
{
	draw(
		Choice(velocity_x, velocity_y), GetX(), GetY()
	);
};

void Hero::UpdateBullet(
	int screenX, int screenY, float mark,
	std::vector<Enemy>& en, std::vector<Block>& bl
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
					en[j].FreeSprite();
					en[j].SetVellY(0.0f);
					en[j].SetVellX(0.0f);
				}
			}
		}
		if (bull[i].Work()) for (int j = 0; j < bl.size(); j++)
		{
			if (bull[i].GetX() + bull[i].GetSpW() <=
				bl[j].GetX() + bl[j].GetSpW() + 2.0f &&
				bull[i].GetX() >= bl[j].GetX() - 2.0f)
			{
				if (bull[i].GetY() + bull[i].GetSpH() <=
					bl[j].GetY() + bl[j].GetSpH() + 2.0f &&
					bull[i].GetY() >= bl[j].GetY() - 2.0f)
				{
					bull[i].SetWork(false);
				}
			}
		}
		if (!bull[i].Work() && bull.capacity())
			ClerBull(i);
	}
	if (bull.size()) for (int i = 0; i < bull.size(); i++)
	{
		if (bull[i].Work())	bull[i].Draw();
	}
	if (bull.capacity() && !bull.size())
	{
		bull.shrink_to_fit();
	}
};