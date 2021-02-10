#include "Hero.h"
#include "Framework.h"

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
	std::vector<Enemy>& en, Map& map
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
		if (bull[i].Work()) 
		{
			for (int k = 0; k < map.GetH(); k++)
			{
				for (int j = 0; j < map.GetW(); j++)
				{
					if (map.map[k][j].work &&
						((int)Type::WATER != map.map[k][j].GetType() &&
						 ((int)Type::LEAAFS) != map.map[k][j].GetType()))
					{
						if (bull[i].GetX() + bull[i].GetSpW() <=
							(float)map.map[k][j].GetX() +
							(float)map.map[k][j].GetSpW() + 2.0f &&
							bull[i].GetX() >=
							(float)map.map[k][j].GetX() - 2.0f)
						{
							if (bull[i].GetY() + bull[i].GetSpH() <=
								(float)map.map[k][j].GetY() +
								(float)map.map[k][j].GetSpH() + 2.0f &&
								bull[i].GetY() >=
								(float)map.map[k][j].GetY() - 2.0f)
							{
								bull[i].SetWork(false);
								if (
									//(int)Type::STEEL != map.map[k][j].GetType() &&
									(int)Type::MONUMENT != map.map[k][j].GetType()
									)
								{
									if (map.map[k][j].GetStatus() == side::COUNT)
									{
										side sd = 
											(bull[i].GetvellX() < 0) ? side::RIGHT :
											(bull[i].GetvellX() > 0) ? side::LEFT :
											(bull[i].GetvellY() < 0) ? side::BOTTOM :
											(bull[i].GetvellY() > 0) ? side::FRONT : side::COUNT;
										map.map[k][j].SetStatus(sd);
										if (sd != side::COUNT)
										{
											getSpriteSize(
												map.map[k][j].GetWallPoss(),
												map.map[k][j].GetRefSizeW(),
												map.map[k][j].GetRefSizeH()
											);
										}
										map.map[k][j].SetPossX(
											(sd == side::LEFT) ? 
											((int)map.map[k][j].GetSpW()) : 0.0f
										);
										map.map[k][j].SetPossY(
											(sd == side::FRONT) ? 
											((int)map.map[k][j].GetSpH()) : 0.f
										);
									}
									else
									{
										map.map[k][j].work = false;
									}
								}
							}
						}
					}
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