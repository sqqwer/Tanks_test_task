#include "Enemy.h"

Enemy::Enemy()
	:	
Animation(), Object(), health(0), live(true)
{};

Enemy::Enemy(tankPreset type,
	const float poss_x, const float poss_y,
	void (*draw)(Sprite*, int, int),
	const int outOfScreenX, const int outOfScreenY
)
	:
	Animation(draw), live(true),
	Object(poss_x, poss_y, outOfScreenX, outOfScreenY) 
{
	Load(type);
};

void Enemy::Shoot(const int outOfScreenX, const int outOfScreenY)
{
	//sd = (side)ShootSide();
	ChioceOutShoot();
	bull.push_back(Bullet(pres.GetBulletAnimPress(),
		(sd == side::LEFT) ? -vellB : (sd == side::RIGHT) ? vellB : 0.0f,
		(sd == side::FRONT) ? -vellB : (sd == side::BOTTOM) ? vellB : 0.0f,
		out_x, out_y, true, drawSprite,
		outOfScreenX, outOfScreenY
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
	drawSprite(
		Choice(velocity_x, velocity_y), GetX(), GetY()
	);
};

void Enemy::UpdateBullet(
	int screenX, int screenY, float mark,
	std::vector<Enemy>& en, Map& map, const int wich,
	const int outOfScreenX, const int outOfScreenY,
	const int heroX, const int heroY,
	const int heroW, const int heroH,
	int& heroHealth
)
{
	for (int i = 0; i < bull.size(); i++)
	{
		bull[i].Update(screenX, screenY, mark, outOfScreenX, outOfScreenY);
		/*if (bull[i].Work()) for (int j = 0; j < en.size(); j++) 
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
		}*/
		if (bull[i].Work())
		{
			if (bull[i].GetX() + bull[i].GetSpW() <=
				heroX + heroW && bull[i].GetX() >= heroX)
			{
				if (bull[i].GetY() + bull[i].GetSpH() <=
					heroY + heroH && bull[i].GetY() >= heroY)
				{
					bull[i].SetWork(false);
					heroHealth--;
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
									if ((int)Type::STEEL != map.map[k][j].GetType())
									{
										if (nowTank == tankPreset::ENEMYTANKARMOR)
										//	||  nowTank == tankPreset::ENEMYTANKPOWER)
										{
											if ((int)Type::MONUMENT != map.map[k][j].GetType())
												map.SetMonumentLive(false);
											if (bull[i].GetvellX() > 0)
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
											if ((int)Type::MONUMENT == map.map[k][j].GetType())
												map.SetMonumentLive(false);
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
	else if (bull.capacity() && !bull.size())
	{
		bull.shrink_to_fit();
	}
};

void Enemy::Update(int w, int h, float spec,
	const int outOfScreenX, const int outOfScreenY
)
{
	possition_x += velocity_x * (spec);
	possition_y += velocity_y * (spec);
	const int right = int(possition_x) + size_w;
	if (possition_x < outOfScreenX)
	{
		possition_x = (float)outOfScreenX;
		velocity_x = -velocity_x;
		velocity_y = 0;
	}
	else if (right >= w)
	{
		possition_x = (float)(w) - size_w;
		velocity_x = -velocity_x;
		velocity_y = 0;
	}
	const int bottom = int(possition_y) + size_h;
	if (possition_y < outOfScreenY)
	{
		possition_y = (float)outOfScreenY;
		velocity_y = -velocity_y;
		velocity_x = 0;
	}
	else if (bottom >= h)
	{
		possition_y = (float)(h) - size_h;
		velocity_y = -velocity_y;
		velocity_x = 0;
	}
};

void Enemy::Colisium(
	const float possX, const float possY,
	const float width, const float height, 
	const float mark, const int magicNumber
)
{
	if (
		possition_x + size_w - 1 >= possX &&
		possition_x + 1 <= possX + width
		)
	{
		if (
			possition_y + size_h - 1 >= possY &&
			possition_y + 1 <= possY + height
			)
		{
			possition_x -= (velocity_x)*mark;
			possition_y -= (velocity_y)*mark;
			velocity_x = 0.0f;
			velocity_y = 0.0f;
		}
	}
};

void Enemy::TankColisium(
	const float possX, const float possY,
	const float width, const float height,
	const float mark, const int magicNumber
)
{
	if (
		possition_x + size_w - 2 >= possX &&
		possition_x + 2 <= possX + width
		)
	{
		if (
			possition_y + size_h - 2 >= possY &&
			possition_y + 2 <= possY + height
			)
		{
			possition_x -= velocity_x * mark;
			possition_y -= velocity_y * mark;
			if (rotateMark > 2.0f)
			{
				rotateMark = 0.0f;
				if (magicNumber % 2 == 0)
				{
					velocity_y = (velocity_x != 0) ? -velocity_x : -velocity_y;
					velocity_x = 0;
				}
				else
				{
					velocity_x = (velocity_y != 0) ? -velocity_y : -velocity_x;
					velocity_y = 0;
				}
			}
		}
	}
};
//Load Preset
void Enemy::Load(tankPreset type)
{
	change = (type == tankPreset::ENEMYTANKARMOR)
		? true : false ;
	if (obj.size()) FreeSprite();
	pres.LoadPreset(type);
	this->health = pres.GetHealth();
	this->speed = pres.GetTankVel();
	this->vellB = pres.GetBulletVel();
	this->reloadTime = pres.GetBulletReload();
	LoadPreset(pres.GetTankAnimPress());
	SetTankPreset(type);
};

void Enemy::ClearAllBullet()
{
	for (int i = 0; i < bull.size(); i++)
	{
		bull[i].FreeSprite();
		bull.erase(bull.begin() + i);
	}
	bull.shrink_to_fit();
};

void Enemy::ClearAllocatedMemory()
{
	if (bull.size())
		ClearAllBullet();
	Animation::FreeSprite();
}