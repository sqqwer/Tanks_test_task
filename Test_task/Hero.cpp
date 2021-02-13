#include "Hero.h"

Hero::Hero()
	:
	Animation(), Object(), health(0), live(true)
{};

Hero::Hero(tankPreset type,
	const float poss_x, const float poss_y,
	void (*draw)(Sprite*, int, int),
	const int outOfScreenX, const int outOfScreenY
)
	:
	Animation(draw), 
	Object(poss_x, poss_y, outOfScreenX, outOfScreenY)
{
	Hero::Load(type);
};
// Function update possiition of object
void Hero::PressKey(FRKey k)
{
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
			if (en.isAlive())
			{
				if (GetTankPreset() >= tankPreset::WIDTHTANK) // FIX IT
				{
					en.SetLive(false);
					en.BackX(en.GetvellX(), mark);
					en.BackY(en.GetvellY(), mark);
					en.SetVellX(0.0f);
					en.SetVellY(0.0f);
				}
				if (en.GetTankPreset() == tankPreset::ENEMYTANKPOWER)
				{
					health = 0;
				}
				else
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
		}
	}
};

void Hero::ReleasedKey()
{
	velocity_x = 0;
	velocity_y = 0;
};

void Hero::Shoot(const int outOfScreenX, const int outOfScreenY)
{
	sd = (side)ShootSide();
	ChioceOutShoot();
	bull.push_back(Bullet(pres.GetBulletAnimPress(),
		(sd == side::LEFT) ? -(vellB + (velocity_x * -1)) :
		(sd == side::RIGHT) ? vellB + velocity_x : 0.0f,
		(sd == side::FRONT) ? -(vellB + (velocity_y * -1)) :
		(sd == side::BOTTOM) ? vellB + velocity_y : 0.0f,
		out_x, out_y, true, drawSprite,
		outOfScreenX, outOfScreenY
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
	drawSprite(
		Choice(velocity_x, velocity_y), GetX(), GetY()
	);
};

void Hero::UpdateBullet(
	int screenX, int screenY, float mark,
	std::vector<Enemy>& en, Map& map,
	const int outOfScreenX, const int outOfScreenY
)
{
	for (int i = 0; i < bull.size(); i++)
	{
		bull[i].Update(screenX, screenY, mark, outOfScreenX, outOfScreenY);
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
					en[j].UpdateHealth(GetPower() ? -2 : -1);
					if (en[j].GetHealth() == 0)
					{
						UpdateKillCount(1);
						en[j].SetLive(false);
						en[j].FreeSprite();
						en[j].SetVellY(0.0f);
						en[j].SetVellX(0.0f);
					}
				}
			}
		}
		if (bull[i].Work()) 
		{
			for (int k = 0; k < map.GetH(); k++)
			{
				for (int j = 0; j < map.GetW(); j++)
				{
					for (int l = 0; l < map.map[k][j].unit.size(); l++)
					{
						if (map.map[k][j].unit[l].GetWorkUnit() &&
							((int)Type::WATER != map.map[k][j].GetType() &&
								(int)Type::LEAAFS != map.map[k][j].GetType()))
						{
							if (bull[i].GetX() + bull[i].GetSpW() <=
								(float)map.map[k][j].unit[l].GetAnimPosX() +
								(float)map.map[k][j].GetSpW() + 2.0f &&
								bull[i].GetX() >=
								(float)map.map[k][j].unit[l].GetAnimPosX() - 2.0f)
							{
								if (bull[i].GetY() + bull[i].GetSpH() <=
									(float)map.map[k][j].unit[l].GetAnimPosY() +
									(float)map.map[k][j].GetSpH() + 2.0f &&
									bull[i].GetY() >=
									(float)map.map[k][j].unit[l].GetAnimPosY() - 2.0f)
								{
									bull[i].SetWork(false);
									if ((int)Type::MONUMENT != map.map[k][j].GetType())
									{

										if ((int)Type::STEEL == map.map[k][j].GetType() &&
											nowTank < tankPreset::HEROTANK4 && !GetPower())
											continue;

										if (GetPower())
										{
											map.map[k][j].unit[0].SetWorkUnit(false);
											map.map[k][j].unit[1].SetWorkUnit(false);
											map.map[k][j].unit[2].SetWorkUnit(false);
											map.map[k][j].unit[3].SetWorkUnit(false);
										}
										if (nowTank > tankPreset::HEROTANK3)
										{
											if(bull[i].GetvellX() > 0)
											{
												if (map.map[k][j].unit[0].GetWorkUnit() ||
													map.map[k][j].unit[2].GetWorkUnit())
												{
													map.map[k][j].unit[0].SetWorkUnit(false);
													map.map[k][j].unit[2].SetWorkUnit(false);
												}
												else
												{
													map.map[k][j].unit[1].SetWorkUnit(false);
													map.map[k][j].unit[3].SetWorkUnit(false);
												}
											}
											if (bull[i].GetvellX() < 0)
											{
												if (map.map[k][j].unit[1].GetWorkUnit() ||
													map.map[k][j].unit[3].GetWorkUnit())
												{
													map.map[k][j].unit[1].SetWorkUnit(false);
													map.map[k][j].unit[3].SetWorkUnit(false);
												}
												else
												{
													map.map[k][j].unit[0].SetWorkUnit(false);
													map.map[k][j].unit[2].SetWorkUnit(false);
												}
											}
											if (bull[i].GetvellY() > 0)
											{
												if (map.map[k][j].unit[0].GetWorkUnit() ||
													map.map[k][j].unit[1].GetWorkUnit())
												{
													map.map[k][j].unit[0].SetWorkUnit(false);
													map.map[k][j].unit[1].SetWorkUnit(false);
												}
												else
												{
													map.map[k][j].unit[2].SetWorkUnit(false);
													map.map[k][j].unit[3].SetWorkUnit(false);
												}
											}
											if (bull[i].GetvellY() < 0)
											{
												if (map.map[k][j].unit[2].GetWorkUnit() ||
													map.map[k][j].unit[3].GetWorkUnit())
												{
													map.map[k][j].unit[2].SetWorkUnit(false);
													map.map[k][j].unit[3].SetWorkUnit(false);
												}
												else
												{
													map.map[k][j].unit[0].SetWorkUnit(false);
													map.map[k][j].unit[1].SetWorkUnit(false);
												}
											}
										}
										else
										{
											map.map[k][j].unit[l].SetWorkUnit(false);
										}
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
//Load Preset
void Hero::Load(tankPreset type)
{
	ClearAllocatedMemory();
	pres.LoadPreset(type);
	this->health = pres.GetHealth();
	this->speed = pres.GetTankVel();
	this->vellB = pres.GetBulletVel();
	this->reloadTime = pres.GetBulletReload();
	LoadPreset(pres.GetTankAnimPress());
	SetTankPreset(type);
};

void Hero::ClearAllBullet()
{
	for (int i = 0; i < bull.size(); i++)
	{
		bull[i].FreeSprite(); 
		bull.erase(bull.begin() + i);
	}
	bull.shrink_to_fit();
};

void Hero::ClearAllocatedMemory()
{
	if (bull.size())
		ClearAllBullet();
	FreeSprite();
}