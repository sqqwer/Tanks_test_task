#include "Logic.h"

#include <iostream>

Logic::Logic()
{};

void Logic::InitAllResources(const char* nameMap, const char* nameLand)
{
	tm = Time(getTickCount);
	land = Land(nameLand, drawSprite);
	upgrade.push_back(Upgrade("./data/upgrade/upgradeArrow.ini", 150, 150, drawSprite, powerUps::UPGRADE));
	upgrade.push_back(Upgrade("./data/upgrade/upgradeArrow.ini", 130, 150, drawSprite, powerUps::UPGRADE));
	upgrade.push_back(Upgrade("./data/upgrade/upgradeArrow.ini", 110, 150, drawSprite, powerUps::UPGRADE));
	upgrade.push_back(Upgrade("./data/upgrade/upgradeBonusGear.ini", 180, 150, drawSprite, powerUps::EXTRALIVE));
	upgrade.push_back(Upgrade("./data/upgrade/darkSidePower.ini", 210, 150, drawSprite, powerUps::MOREPOWER));
	map.LoadMap(nameMap, drawSprite);
	hero = Hero(tankPreset::HEROTANK1, 200, 200, drawSprite);
};

bool Logic::CheackInitConstructor()
{
	if (!land.GetStatus())
	{
		std::cout << "Logic : Couldn't load Land file!" << std::endl;
		return false;
	}
	if (!map.GetStatus())
	{
		std::cout << "Logic : Couldn't load Map file!" << std::endl;
		return false;
	}
	if (!hero.GetStatus())
	{
		std::cout << "Logic : Couldn't load Hero preset file!" << std::endl;
		return false;
	}
	for (auto i : upgrade)
	{
		for (int j = 0; j < i.unit.size(); j++)
		{
			if (!i.unit[j].Animation::GetStatus())
			{
				std::cout << "Logic : Couldn't load Upgrade file!" << std::endl;
				return false;
			}
		}
	}
	return true;
};

bool Logic::InitSpriteSize()
{
	if (CheackInitConstructor())
	{
		for (int i = 0; i < upgrade.size(); i++)
		{
			if (upgrade[i].GetLiveBlock())
				for (int j = 0; j < upgrade[i].unit.size(); j++)
					getSpriteSize(
						upgrade[i].unit[j].GetSprite(), 
						upgrade[i].GetRefSizeW(), 
						upgrade[i].GetRefSizeH()
					);
		}
		for (int i = 0; i < enemy.size(); i++)
		{
			getSpriteSize(enemy[i].GetSprite(), enemy[i].GetRefSizeW(), enemy[i].GetRefSizeH());
		}
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
	mark = tm.Mark(); spawMark += mark;
	hero.UpdateReloadMark(mark); map.UpdateMark(mark);
	land.Draw(); 
	DrawUpgrade(mark); hero.Draw();
	map.DrawMap(map.GetRefMark()); hero.TickTimer(-mark);
};

void Logic::PowerUpsColisium()
{
	for (int i = 0; i < upgrade.size(); i++) 
		if (upgrade[i].GetLiveBlock())
			upgrade[i].PowerUpsColisium(hero);
}

void Logic::DrawUpgrade(const float mark)
{
	for (int i = 0; i < upgrade.size(); i++)
	{
		if (upgrade[i].GetLiveBlock())
		{
			upgrade[i].Upgrade::Draw();
			upgrade[i].UpdateMark(mark);
		}
	}
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
					for (int k = 0; k < map.map[i][j].unit.size(); k++)
					{
						if (map.map[i][j].unit[k].GetWorkUnit() )
						{
							hero.Object::Colisium(
								(float)map.map[i][j].unit[k].GetAnimPosX(),
								(float)map.map[i][j].unit[k].GetAnimPosY(),
								(float)map.map[i][j].GetSpW(), (float)map.map[i][j].GetSpH(),
								mark
							);
						}
					}
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
	if (spawMark > 2.0f)
	{
		CheckSpawnEnemy();
		spawMark = 0;
	}
};

void Logic::UpdateHeroTank(const int screenX, const int screenY)
{
	hero.UpdateBullet(screenX, screenY, mark, enemy, map);
	hero.Update(screenX, screenY, mark);
	PowerUpsColisium();
	for (int i = 0; i < upgrade.size(); i++)
	{
		if (!upgrade[i].GetLiveBlock())
		{
			upgrade[i].ClearBlock();
			upgrade.erase(upgrade.begin() + i);
		}
	}
	
	WallHeroColisium();
	if (hero.GetPowerTimer() < 0)
		hero.SetPower(false);

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
						for (int l = 0; l < map.map[k][j].unit.size(); l++)
						{
							enemy[i].Enemy::Colisium(
								(float)map.map[k][j].unit[l].GetAnimPosX(),
								(float)map.map[k][j].unit[l].GetAnimPosY(),
								(float)map.map[k][j].GetSpW(),
								(float)map.map[k][j].GetSpH(), mark
							);
						}
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
	for (int i = 0; i < upgrade.size(); i++)
		upgrade[i].ClearBlock();
};

void Logic::ClearLand()
{
	land.ClearLand();
};

void Logic::CheckSpawnEnemy()
{
	if (enemyCount > 0)
	{
		for (int i = 0; i < map.enemySpawn.size(); i++)
		{
			if (!enemy.size())
			{
				enemy.push_back(
					Enemy(tankPreset::HEROTANK1, map.enemySpawn[i].posX, map.enemySpawn[i].posY, drawSprite)
				);
				getSpriteSize(enemy[enemy.size() - 1].GetSprite(), enemy[enemy.size() - 1].GetRefSizeW(), enemy[enemy.size() - 1].GetRefSizeH());
				enemy[enemy.size() - 1].SetVellY(-50);
				--enemyCount;
			}
			else
			{
				if (SpawnPointClear(map.enemySpawn[i]))
				{
					enemy.push_back(
						Enemy(tankPreset::HEROTANK1, map.enemySpawn[i].posX, map.enemySpawn[i].posY, drawSprite)
					);
					getSpriteSize(enemy[enemy.size() - 1].GetSprite(), enemy[enemy.size() - 1].GetRefSizeW(), enemy[enemy.size() - 1].GetRefSizeH());
					enemy[enemy.size() - 1].SetVellY(-50);
					--enemyCount;
				}
			}
		}
	}
};

bool Logic::SpawnPointClear(struct possition enSp)
{
	for (int j = 0; j < enemy.size(); j++)
	{
		if (enemy[j].Object::GetX() + enemy[j].GetSpW() >= enSp.posX &&
			enemy[j].Object::GetX() <= enSp.posX + enemy[j].GetSpW())
		{
			if (enemy[j].Object::GetY() + enemy[j].GetSpH() >= enSp.posY &&
				enemy[j].Object::GetY() <= enSp.posY + enemy[j].GetSpH())
			{
				return false;
			}
		}
	}
	return true;
};