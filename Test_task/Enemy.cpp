#include "Enemy.h"

Enemy::Enemy()
	:
	Animation(), Object(), alives(0), live(true),
	out_x(0.0f), out_y(0.0f)
{};

Enemy::Enemy(
	const char* name_ini, const char* bull_preset,
	int lives, const float poss_x, const float poss_y,
	void (*draw)(Sprite*, int, int)
)
	:
	Animation(name_ini, draw), bull_preset(bull_preset),
	Object(poss_x, poss_y), alives(lives), live(true),
	out_x(0.0f), out_y(0.0f)
{};

void Enemy::Shoot()
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
};

void Enemy::ClerBull(const unsigned int elem)
{
	bull[elem].FreeSprite(); bull.erase(bull.begin() + elem);
};

void Enemy::Draw()
{
	draw(
		Choice(velocity_x, velocity_y), GetX(), GetY()
	);
};

void Enemy::UpdateBullet(
	int screenX, int screenY, float mark,
	std::vector<Enemy>& en,
	std::vector<Block>& bl,
	const int wich 
)
{
	for (int i = 0; i < bull.size(); i++)
	{
		bull[i].Update(screenX, screenY, mark);
		if (bull[i].Work()) for (int j = 0; j < en.size(); j++) 
		if (en[j].isAlive())
		{
				if (wich == j) continue;
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
						en[j].FreeSprite();
					}
				}
		}
		if (bull[i].Work())
			for (int j = 0; j < bl.size(); j++)
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
	else if (bull.capacity() && !bull.size())
	{
		bull.shrink_to_fit();
	}
};

void Enemy::Update(int w, int h, float spec)
{
	const int out = 30;
	possition_x += velocity_x * (spec);
	possition_y += velocity_y * (spec);
	const int right = static_cast<int>(possition_x) + size_w;
	if (possition_x < out)
	{
		possition_x = static_cast<float>(out);
		velocity_x = -velocity_x;
		velocity_y = 0;
	}
	else if (right >= w)
	{
		possition_x = static_cast<float>(w) - size_w;
		velocity_x = -velocity_x;
		velocity_y = 0;
	}
	const int bottom = static_cast<int>(possition_y) + size_h;
	if (possition_y < out)
	{
		possition_y = static_cast<float>(out);
		velocity_y = -velocity_y;
		velocity_x = 0;
	}
	else if (bottom >= h)
	{
		possition_y = static_cast<float>(h) - size_h;
		velocity_y = -velocity_y;
		velocity_x = 0;
	}
};

void Enemy::Colisium(
	const float possX, const float possY,
	const float width, const float height, const float mark
)
{
	if (
		possition_x + size_w >= possX - width &&
		possition_x - size_w <= possX + width
		)
	{
		if (
			possition_y + size_h >= possY - height &&
			possition_y - size_h <= possY + height
			)
		{
			possition_x -= (velocity_x)*mark;
			possition_y -= (velocity_y)*mark;
			if (!velocity_x)
				velocity_y = -velocity_y;
			else if (!velocity_y)
				velocity_x = -velocity_x;
		}
	}
};

void Enemy::TankColisium(
	const float possX, const float possY,
	const float width, const float height, const float mark
)
{
	if (
		possition_x + size_w >= possX &&
		possition_x <= possX + width
		)
	{
		if (
			possition_y + size_h >= possY &&
			possition_y <= possY + height
			)
		{
			if (!velocity_y)
			{
				possition_x -= velocity_x * mark;
			}
			else if (!velocity_x)
			{
				possition_y -= velocity_y * mark;
			}
			velocity_x = 0;
			velocity_y = 0;
		}
	}
};