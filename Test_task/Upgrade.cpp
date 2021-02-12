#include "Upgrade.h"

Upgrade::Upgrade()
	:
	Block()
{};

Upgrade::Upgrade(
	const char* name, const float possX, const float possY,
	void (*draw)(Sprite*, int, int), const powerUps type
)
	:
	Block(name, possX, possY, 0, false), powerType(type)
{
	SetLiveBlock(true);
};

void Upgrade::PowerUpsColisium(Hero& hero)
{
	if (possition_x + size_w - 2 >= hero.GetX() &&
		possition_x + 2 <= hero.GetX() + hero.GetSpW())
	{
		if (possition_y + size_h - 2 >= hero.GetY() &&
			possition_y + 2 <= hero.GetY() + hero.GetSpH())
		{
			if (GetPowerType() == powerUps::EXTRALIVE)
			{
				hero.AddLives(1);	SetLiveBlock(false);
				hero.GetInfo();
			}
			if (GetPowerType() == powerUps::UPGRADE)
			{
				if (hero.GetTankPreset() >= tankPreset::HEROTANK1 && 
					hero.GetTankPreset() < tankPreset::HEROTANK3)
				{
					hero.Load((tankPreset)((int)hero.GetTankPreset() + 1));
					getSpriteSize(hero.GetSprite(), hero.GetRefSizeW(), hero.GetRefSizeH());
					hero.GetInfo();
				}
				SetLiveBlock(false);
			}
			if (GetPowerType() == powerUps::MOREPOWER)
			{
				hero.SetTimer(powerTimer);
				hero.SetPower(true);
				SetLiveBlock(false);
			}
		}
	}
};

void Upgrade::Draw()
{
	for (int i = 0; i < unit.size(); i++)
	{
		if (GetLiveBlock())
		{
			if (GetMark() <= GetConstTime())
			{
				drawSprite(unit[i].GetSprite(), GetX(), GetY());
			}
			else
			{
				if (GetMark() >= GetConstTime() + lifeTime)
				{
					ClearMark();
					reloadTime -= 0.05f;
				}
			}
		}
	}
};