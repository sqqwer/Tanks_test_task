#include "Logic.h"

#include <cmath>
#include <iostream>
#include <thread>

Logic::Logic()
{};

void Logic::InitAllResources(const char* nameMap, const char* nameLand,
	const int sizeScreenW, const int sizeScreenH
)
{
	tm = Time(getTickCount);
	this->sizeScreenW = sizeScreenW; this->sizeScreenH = sizeScreenH;
	land = Land(nameLand, drawSprite); 
	LoadArrayMap(nameMap);
	getSpriteSize(land.GetSprite(), land.GetRefSizeW(), land.GetRefSizeH());
	InitOutOfScreen(); 
	land.SetPossitionX((float)outOfScreenW); 
	land.SetPossitionY((float)outOfScreenH);
	InitPossitionUpgrade(); 
	spawnExtraLifeTimer = 10.f; 
	spawnDrakSidePower = 40.f;
	hero.SetLives(3);
	enemyUnit = struct enemySpawnTypes(5, 5, 5, 5);
	LoadNewMap(archiveMap[archivePossition++].c_str());
	hero = Hero(tankPreset::HEROTANK1, map.GetHszX(), map.GetHszY(), drawSprite, outOfScreenW, outOfScreenH);
};

void Logic::InitOutOfScreen()
{
	outOfScreenW = (sizeScreenW - land.GetSpW()) / 2;
	outOfScreenH = (sizeScreenH - land.GetSpH()) / 2;
};

void Logic::InitPossitionUpgrade()
{
	std::uniform_int_distribution<int> unitX(outOfScreenW + 30, GetDifferenceW() - 30);
	std::uniform_int_distribution<int> unitY(outOfScreenH + 30, GetDifferenceH() - 30);
	for (int i = 0; i < 16; i++)
	{
		spawnUpgrade[i] = struct possition((float)unitX(rd), (float)unitY(rd));
	}
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
	mark = tm.Mark(); UpdateSpawnEnemyMark(mark);
	hero.UpdateReloadMark(mark); map.UpdateMark(mark);
	land.Draw();
	spawnExtraLifeTimer -= mark;
	//spawnDrakSidePower -= mark;
	enemyChoosetargetMark += mark;
	enemyUpdatePossitionMark += mark; hero.Draw();
	DrawEnemy();
	
	map.DrawMap(map.GetRefMark());
	hero.TickTimer(-mark);
	if (enemyUpdatePossitionMark > 1.5f)
	{
		MoveToTarget();
		enemyUpdatePossitionMark = 0.0f;
	}
	std::thread first( [this]
		{ this->ChooseTarget(); }
	);
	if (enemyChoosetargetMark > 4.0f)
	{
		
		//enemyChoosetargetMark = 0.0f;
	}
	first.join();
};

void Logic::PowerUpsColisium()
{
	for (int i = 0; i < upgrade.size(); i++)
	{
		if (upgrade[i].GetLiveBlock())
			upgrade[i].PowerUpsColisium(hero);
	}
};

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
};

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
								(float)map.map[i][j].GetSpW(), 
								(float)map.map[i][j].GetSpH(), mark
							);
						}
					}
				}
			}
		}
	}
};

bool Logic::UpdateTank()
{
	Draw();
	UpdateHeroTank();
	/*std::thread first([this]
		{ this->UpdateEnemyTank(); }
	);*/
	UpdateEnemyTank();
	std::thread second([this] 
		{ this->CanSHoot(); }
	);
	if (!map.GetMonumentLive() || hero.GetLives() <= 0)
	{
		std::string out((!map.GetMonumentLive()) ? "Base is falling" : "Tank destroyed");
		std::cout << "You Lose : " << out << std::endl;
		return true;
	}
	SpawnUpgrade();
	DrawUpgrade(mark);
	if (GetSpawnEnemyMark() > 5.0f || !enemy.size())
	{
		CheckSpawnEnemy(); ClearSpawnEnemyMark();
	}
	if (!enemyCount && !enemy.size())
	{
		ClearUpgrade();
		hero.SetLives(3);
		enemyUnit = struct enemySpawnTypes(5, 5, 5, 5);
		LoadNewMap(archiveMap[archivePossition++].c_str());
		if (archivePossition >= archiveMap.size())
			archivePossition = 0;
		hero.SetPossitionX(map.GetHszX()); hero.SetPossitionY(map.GetHszY());
		enemyCount = 20;
	}
	//first.join();
	second.join();
	return false;
};

void Logic::UpdateHeroTank()
{
	hero.UpdateBullet(GetDifferenceW(), GetDifferenceH(), mark, enemy, map,
		outOfScreenW, outOfScreenH
	);
	hero.Update(GetDifferenceW(), GetDifferenceH(), mark);
	PowerUpsColisium();
	if (!hero.GetHealth())
	{
		hero.UpdateLives(-1);
		hero.Load(tankPreset::HEROTANK1);
		getSpriteSize(hero.GetSprite(), hero.GetRefSizeW(), hero.GetRefSizeH());
		hero.SetPossitionX(map.GetHszX()); hero.SetPossitionY(map.GetHszY());
	}
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
	prevHeroKill = hero.GetKillCount();
};

void Logic::UpdateEnemyTank()
{
	std::uniform_int_distribution<int> magicNuber(0,10);
	for (int i = 0; i < enemy.size(); i++)
	{
		if (enemy[i].isAlive() && enemy[i].GetHealth() == 1 && enemy[i].GetChange() &&
			enemy[i].GetTankPreset() == tankPreset::ENEMYTANKARMOR)
		{
			enemy[i].SetChange(false);
			enemy[i].LoadPreset("./data/tank/init/armorTankSec.ini");
			getSpriteSize(enemy[i].GetSprite(), enemy[i].GetRefSizeW(), enemy[i].GetRefSizeH());
		}
		enemy[i].UpdateReloadMark(mark); enemy[i].UpdateRotateMark(mark);
		enemy[i].UpdateBullet(GetDifferenceW(), GetDifferenceH(), mark, enemy, map, i,
			outOfScreenW, outOfScreenH,
			hero.GetX(), hero.GetY(), hero.GetSpW(), hero.GetSpH(), hero.GetRefenceHealth()
		);
		if (enemy[i].isAlive())
		{
			enemy[i].UpdateReloadMark(mark);
			enemy[i].Update(GetDifferenceW(), GetDifferenceH(), mark, outOfScreenW, outOfScreenH);
			hero.Hero::TankColisium(enemy[i], mark);
			for (int j = 0; j < enemy.size(); j++)
			{
				if (i != j && (enemy[i].isAlive() && enemy[j].isAlive()))
					enemy[i].Enemy::TankColisium(
						(float)enemy[j].GetX(), (float)enemy[j].GetY(),
						(float)enemy[j].GetSpW(), (float)enemy[j].GetSpH(),
						mark, magicNuber(rd)
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
								(float)map.map[k][j].GetSpH(), mark, magicNuber(rd)
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
		int size = (hero.GetTankPreset() == tankPreset::HEROTANK3 ||
					hero.GetTankPreset() == tankPreset::HEROTANK4)
			? 2 : 1 ;
		if (hero.bull.size() < size)
		{
			hero.ClearReloadMark();
			hero.Shoot(GetDifferenceW(), GetDifferenceH());
			getSpriteSize(
				hero.bull[hero.bull.size() - 1].GetSprite(),
				hero.bull[hero.bull.size() - 1].GetRefSizeW(),
				hero.bull[hero.bull.size() - 1].GetRefSizeH()
			);
		}
	}
};

void Logic::LoadNewMap(const char* nameOfMap)
{
	if (map.GetStatus()) map.ClearMemory();
	map.AlocateMemory();
	map.LoadMap(nameOfMap, drawSprite, 
		outOfScreenW, outOfScreenH
	);
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

tankPreset Logic::ChooseType()
{
	if (enemyUnit.enemyEasy > 0)
	{
		enemyUnit.enemyEasy--;
		return tankPreset::ENEMYTANKEASY;
	}
	else if (enemyUnit.enemyFast > 0)
	{
		enemyUnit.enemyFast--;
		return tankPreset::ENEMYTANKFAST;
	}
	else if (enemyUnit.enemyPower > 0)
	{
		enemyUnit.enemyPower--;
		return tankPreset::ENEMYTANKPOWER;
	}
	else if (enemyUnit.enemyArmor > 0)
	{
		enemyUnit.enemyArmor--;
		return tankPreset::ENEMYTANKARMOR;
	}
	return tankPreset::ENEMYTANKEASY;
};

void Logic::CheckSpawnEnemy()
{
	if (GetEnemyCount() > 0 && enemy.size() < 3)
	{
		if (++enemySpawPossition >= map.enemySpawn.size())
			enemySpawPossition = 0;
		for (int i = enemySpawPossition; i < map.enemySpawn.size(); i++)
		{

			if (SpawnPointClear(map.enemySpawn[i]))
			{
				enemy.push_back(
					Enemy(ChooseType(), map.enemySpawn[i].posX, map.enemySpawn[i].posY, drawSprite,
						outOfScreenW, outOfScreenH)
				);
				getSpriteSize(enemy[enemy.size() - 1].GetSprite(),
					enemy[enemy.size() - 1].GetRefSizeW(), enemy[enemy.size() - 1].GetRefSizeH());
				--enemyCount;
				break;
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
	if (hero.Object::GetX() + hero.GetSpW() >= enSp.posX &&
		hero.Object::GetX() <= enSp.posX + hero.GetSpW())
	{
		if (hero.Object::GetY() + hero.GetSpH() >= enSp.posY &&
			hero.Object::GetY() <= enSp.posY + hero.GetSpH())
		{
			return false;
		}
	}

	return true;
};

void Logic::DrawEnemy()
{
	for (int i = 0; i < enemy.size(); i++)
	{
		if (enemy[i].isAlive())
		{
			enemy[i].Draw();
			for (int j = 0; j < enemy[i].bull.size(); j++)
			{
				if (enemy[i].bull[j].Work())
				{
					enemy[i].bull[j].Draw();
				}
			}
		}
	}
};

void Logic::SpawnUpgrade()
{
	if (upgrade.size() <= 16)
	{
		if (hero.GetKillCount() >= 3)
		{
			CheckSpawnUpgrade(
				"./data/upgrade/upgradeArrow.ini", powerUps::UPGRADE
			);
			hero.UpdateKillCount(-hero.GetKillCount());
		}
		if (spawnExtraLifeTimer < 0 && hero.GetHealth() < 4)
		{
			CheckSpawnUpgrade(
				"./data/upgrade/upgradeBonusGear.ini", powerUps::EXTRALIVE
			);
			spawnExtraLifeTimer = 25.0f;
		}
		if (spawnDrakSidePower < 0)
		{
			CheckSpawnUpgrade(
				"./data/upgrade/darkSidePower.ini", powerUps::MOREPOWER
			);
			spawnDrakSidePower = 20.0f;
		}
	}
};

void Logic::CheckSpawnUpgrade(const char* name, powerUps type)
{
	if (spawnUpgradePossition >= 16) spawnUpgradePossition = 0;
	for (int& i = spawnUpgradePossition; i < 16; i++)
	{
		if (lastUpgradePossiotion != spawnUpgrade[i]
			&& CheckSpawnPoss(spawnUpgrade[i]))
		{
			upgrade.push_back(Upgrade(name, spawnUpgrade[i].posX, 
				spawnUpgrade[i].posY, drawSprite, type)
			);
			getSpriteSize(
				upgrade[upgrade.size() - 1].
					unit[upgrade[upgrade.size() - 1].unit.size() - 1].GetSprite(),
				upgrade[upgrade.size() - 1].GetRefSizeW(),
				upgrade[upgrade.size() - 1].GetRefSizeH()
			);
			lastUpgradePossiotion = spawnUpgrade[i]; break;
		}
	}
};

bool Logic::CheckSpawnPoss(struct possition elem)
{
	for (int i = 0; i < map.GetH(); i++)
	{
		for (int j = 0; j < map.GetW(); j++)
		{
			if (map.map[i][j].GetType() == (int)Type::MONUMENT ||
				map.map[i][j].GetType() == (int)Type::WATER ||
				map.map[i][j].GetType() == (int)Type::STEEL)
			if (
				map.map[i][j].GetX() + map.map[i][j].GetSpW() >= elem.posX &&
				map.map[i][j].GetX() <= elem.posX + map.map[i][j].GetSpW()
				)
			{
				if (
					map.map[i][j].GetY() + map.map[i][j].GetSpH() >= elem.posY &&
					map.map[i][j].GetY() <= elem.posY + map.map[i][j].GetSpH()
					)
				{
					return false;
				}
			}
		}
	}
	return true;
};

float Logic::LenghtToObject(
	float object1PosX, float object1PosY,
	float object2PosX, float object2PosY
)
{
	return (std::sqrt(
		(object1PosX - object2PosX)* (object1PosX - object2PosX)+
		(object1PosY - object2PosY)* (object1PosY - object2PosY))
	);
};

void Logic::ChooseTarget()
{
	float lenghtToHero = 0;
	float lenghtToMonument = 0;
	for (int i = 0; i < enemy.size(); i++)
	{
		const float possEnX = (float)enemy[i].GetX();
		const float possEnY = (float)enemy[i].GetY();

		const float enemySizeW = (float)enemy[i].GetSpW();
		const float enemySizeH = (float)enemy[i].GetSpH();

		const float possHeX = (float)hero.GetX();
		const float possHeY = (float)hero.GetY();

		const float possMoX = (float)map.GetMonumentX();
		const float possMoY = (float)map.GetMonumentY();

		lenghtToHero= LenghtToObject(possEnX, possEnY, possHeX, possHeY);
		lenghtToMonument = LenghtToObject(possEnX, possEnY, possMoX, possMoY);

		if ((possEnY + enemySizeH / 2 >= possHeY + enemySizeH / 2 && 
			possEnY - enemySizeH / 2 <= possHeY + enemySizeH / 2) || 
			(possEnX + enemySizeH / 2 >= possHeX + enemySizeH / 2 &&
				possEnX - enemySizeH / 2 <= possHeX + enemySizeH / 2))
		{
			enemy[i].SetTraget(1);
			continue;
		}
		else if (
			((possEnY + enemySizeH / 2 >= possMoY + enemySizeH / 2 &&
				possEnY - enemySizeH / 2 <= possMoY + enemySizeH / 2) ||
				(possEnX + enemySizeH / 2 >= possMoX + enemySizeH / 2 &&
					possEnX - enemySizeH / 2 <= possMoX + enemySizeH / 2)))
		{
			enemy[i].SetTraget(0);
			continue;
		}

		if (lenghtToHero < lenghtToMonument)
		{
			enemy[i].SetTraget(1);
		}
		else
		{
			enemy[i].SetTraget(0);
		}
	}
};

void Logic::MoveToTarget()
{
	for (int i = 0; i < enemy.size(); i++)
	{
		const float possEnX = (float)enemy[i].GetX();
		const float possEnY = (float)enemy[i].GetY();

		const float possObjX = (float)(enemy[i].GetTarget()) ? (float)hero.GetX() : map.GetMonumentX();
		const float possObjY = (float)(enemy[i].GetTarget()) ? (float)hero.GetY() : map.GetMonumentY();
		
		float x = (float)(possEnX > possObjX) ? possEnX - possObjX : possObjX - possEnX;
		float y = (float)(possEnY > possObjY) ? possEnY - possObjY : possObjY - possEnY;
		
		if (y < x)
		{
			if (possEnX > possObjX)
			{
				enemy[i].SetVellX(-75.0f);
			}
			else if (possEnX < possObjX)
			{
				enemy[i].SetVellX(75.0f);
			}
			enemy[i].SetVellY(0.0f);
		}
		if (y > x)
		{
			if (possEnY > possObjY)
			{
				enemy[i].SetVellY(-75.0f);
			}
			else if (possEnY < possObjY)
			{
				enemy[i].SetVellY(75.0f);
			}
			enemy[i].SetVellX(0.0f);
		}
	}
};

void Logic::LoadArrayMap(const char* name_ini)
{
	std::ifstream mapFile;
	mapFile.open(name_ini);
	if (mapFile.is_open()) while (!mapFile.eof())
	{
		std::string tmp;
		mapFile >> tmp;
		if (tmp[0] == '#') continue;
		archiveMap.push_back(tmp);
	}
	archivePossition = 0;
	mapFile.close();
};

void Logic::CanSHoot()
{
	for (int i = 0; i < enemy.size(); i++)
	{
		if (enemy[i].bull.size() < 1 && 
			enemy[i].GetReloadMark() > enemy[i].GetReloadConstTime()
			)
		{
			enemy[i].ClearReloadMark();
			const float possEnX = (float)enemy[i].GetX();
			const float possEnY = (float)enemy[i].GetY();
			
			const float enemySizeW = (float)enemy[i].GetSpW();
			const float enemySizeH = (float)enemy[i].GetSpH();

			const float possObjX = (float)(enemy[i].GetTarget()) ? (float)hero.GetX() : map.GetMonumentX();
			const float possObjY = (float)(enemy[i].GetTarget()) ? (float)hero.GetY() : map.GetMonumentY();

			if (possEnY + enemySizeH / 2 >= possObjY + enemySizeH / 2
				&& possEnY - enemySizeH / 2 <= possObjY + enemySizeH / 2)
			{
				if (possEnX > possObjX)
				{
					enemy[i].SetVellX(-75.0f);
				}
				else if (possEnX < possObjX)
				{
					enemy[i].SetVellX(75.0f);
				}
				enemy[i].SetVellY(0.0f);
				enemy[i].SetSide((possEnX > possObjX) ? side::LEFT : side::RIGHT);
				enemy[i].Shoot(outOfScreenW, outOfScreenH);
			}
			else if (possEnX + enemySizeH / 2 >= possObjX + enemySizeH / 2 &&
				possEnX - enemySizeH / 2 <= possObjX + enemySizeH / 2)
			{
				if (possEnY > possObjY)
				{
					enemy[i].SetVellY(-75.0f);
				}
				else if (possEnY < possObjY)
				{
					enemy[i].SetVellY(75.0f);
				}
				enemy[i].SetVellX(0.0f);
				enemy[i].SetSide((possEnY > possObjY) ? side::FRONT : side::BOTTOM);
				enemy[i].Shoot(outOfScreenW, outOfScreenH);
			}
			else
			{
				enemy[i].SetSide((side)enemy[i].ShootSide());
				enemy[i].Shoot(outOfScreenW, outOfScreenH);
			}
		}
	}
};