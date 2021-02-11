#include "Logic.h"

#include <iostream>

Logic::Logic()
{};

void Logic::InitAllResources(const char* nameMap, const char* nameLand)
{
	tm = Time(getTickCount);
	land = Land(nameLand, drawSprite);
	upgrade.SetStatus(side::COUNT);
	upgrade = Upgrade("upgrade.ini", 150, 150, drawSprite);
	map.LoadMap(nameMap, drawSprite);
	hero = Hero(tankPreset::HEROTANK1, map.GetHszX(), map.GetHszY(), drawSprite);
};

bool Logic::CheackInitConstructor()
{
	if (!land.GetStatus())
	{
		std::cout << "Logic : Can't load Land file!" << std::endl;
		return false;
	}
	if (!map.GetStatus())
	{
		std::cout << "Logic : Can't load Map file!" << std::endl;
		return false;
	}
	if (!hero.GetStatus())
	{
		std::cout << "Logic : Can't load Hero preset file!" << std::endl;
		return false;
	}
	if (!upgrade.Animation::GetStatus())
	{
		std::cout << "Logic : Can't load Upgrade file!" << std::endl;
		return false;
	}
	return true;
};

bool Logic::InitSpriteSize()
{
	if (CheackInitConstructor())
	{
		getSpriteSize(upgrade.GetSprite(), upgrade.GetRefSizeW(), upgrade.GetRefSizeH());
		getSpriteSize(land.GetSprite(), land.GetRefSizeW(), land.GetRefSizeH());
		getSpriteSize(hero.GetSprite(), hero.GetRefSizeW(), hero.GetRefSizeH());
		map.GetMapSpriteSize();
	}
	else
	{
		return false;
	}
	return true;
};

void Logic::Draw()
{
	mark = tm.Mark();
	hero.UpdateReloadMark(mark); map.mark += mark; upgrade.UpdateMark(mark);
	land.Draw(); hero.Draw(); map.DrawMap(map.mark); upgrade.Upgrade::Draw();
};

void Logic::PowerUpsColisium()
{
	upgrade.PowerUpsColisium(hero);
}

void Logic::WallHeroColisium()
{
	for (int i = 0; i < map.GetH(); i++)
	{
		for (int j = 0; j < map.GetW(); j++)
		{
			if (map.map[i][j].GetLiveBlock())
			{
				if ((int)Type::LEAAFS != map.map[i][j].GetType())
				{
					hero.Object::Colisium(
						(float)map.map[i][j].GetX(), (float)map.map[i][j].GetY(),
						(float)map.map[i][j].GetSpW(), (float)map.map[i][j].GetSpH(),
						mark
					);
				}
			}
		}
	}
};

void Logic::UpdateTank(const int screenX, const int screenY)
{
	Draw();
	UpdateHeroTank(screenX, screenY);
	UpdateEnemyTank(screenX, screenY);
};

void Logic::UpdateHeroTank(const int screenX, const int screenY)
{
	hero.UpdateBullet(screenX, screenY, mark, enemy, map);
	hero.Update(screenX, screenY, mark);
	PowerUpsColisium(); WallHeroColisium();
	if (hero.GetX() > 450)
	{
		LoadNewMap("Map2.ini");
	}
};

void Logic::UpdateEnemyTank(const int screenX, const int screenY)
{
	for (int i = 0; i < enemy.size(); i++)
	{
		enemy[i].UpdateBullet(screenX, screenY, mark, enemy, map, i);
		if (enemy[i].isAlive())
		{
			enemy[i].UpdateReloadMark(mark);
			enemy[i].Update(screenX, screenY, mark);
			enemy[i].Draw();
			hero.Hero::TankColisium(enemy[i], mark);
			for (int j = 0; j < enemy.size(); j++)
			{
				if (i != j && (enemy[i].isAlive() && enemy[j].isAlive()))
					enemy[i].Enemy::TankColisium(
						(float)enemy[j].GetX(), (float)enemy[j].GetY(),
						(float)enemy[j].GetSpW(), (float)enemy[j].GetSpH(), mark
					);
			}
			for (int k = 0; k < map.GetH(); k++)
			{

				for (int j = 0; j < map.GetW(); j++)
				{
					if (map.map[k][j].GetLiveBlock() && enemy[i].isAlive() &&
						(int)Type::LEAAFS != map.map[k][j].GetType())
					{
						enemy[i].Enemy::Colisium(
							(float)map.map[k][j].GetX(),
							(float)map.map[k][j].GetY(),
							(float)map.map[k][j].GetSpW(),
							(float)map.map[k][j].GetSpH(), mark
						);
					}
				}
			}
		}
		else if (!enemy[i].isAlive() && !enemy[i].bull.size() &&
			!enemy[i].bull.capacity())
		{
			enemy[i].ClearAllocatedMemory();
			enemy.erase(enemy.begin() + i);
		}
	}
	if (enemy.capacity() && !enemy.size())
	{
		ClearAllEnemy();
	}
};

void Logic::PressedKey(FRKey k) {
	hero.PressKey(k);
};

void Logic::ReleasedKey(FRKey k) {
	hero.ReleasedKey();
};

void Logic::UpdateMouseClick(FRMouseButton button, bool isReleased)
{
	if (button == FRMouseButton::LEFT && isReleased && 
		hero.GetReloadMark() > hero.GetReloadConstTime())
	{
		hero.ClearReloadMark();	hero.Shoot();
		getSpriteSize(
			hero.bull[hero.bull.size() - 1].GetSprite(),
			hero.bull[hero.bull.size() - 1].GetRefSizeW(),
			hero.bull[hero.bull.size() - 1].GetRefSizeH()
		);
	}
};

void Logic::LoadNewMap(const char* nameOfMap)
{
	map.ClearMemory();
	map.AlocateMemory();
	map.LoadMap(nameOfMap, drawSprite);
	map.GetMapSpriteSize();
};

void Logic::CloseProgram()
{
	ClearLand();
	ClearUpgrade();
	ClearAllEnemy();
	map.ClearMemory();
	hero.ClearAllocatedMemory();
};

void Logic::ClearAllEnemy()
{
	for (int i = 0; i < enemy.size(); i++)
	{
		enemy[i].ClearAllocatedMemory();
		enemy.erase(enemy.begin() + i);
	}
	enemy.shrink_to_fit();
};

void Logic::ClearUpgrade()
{
	upgrade.ClearBlock();
};

void Logic::ClearLand()
{
	land.ClearLand();
}