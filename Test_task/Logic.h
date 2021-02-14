#pragma once

#include "Map.h"
#include "Land.h"
#include "Hero.h"
#include "Time.h"
#include "Enemy.h"
#include "Block.h"
#include "Bullet.h"
#include "Upgrade.h"

#include "Framework.h"

#include <random>
#include <fstream>

struct enemySpawnTypes {
	enemySpawnTypes()
		: 
		enemyEasy(0), enemyFast(0),
		enemyPower(0), enemyArmor(0)
	{};
	enemySpawnTypes(
		const int enemyEasy, const int enemyFast,
		const int enemyPower, const int enemyArmor
	)
		:
		enemyEasy(enemyEasy), enemyFast(enemyFast),
		enemyPower(enemyPower), enemyArmor(enemyArmor)
	{};

	int enemyEasy;
	int enemyFast;
	int enemyPower;
	int enemyArmor;
};

class Logic
{
public:
	Logic();
	float LenghtToObject(
		float object1PosX, float object1PosY,
		float object2PosX, float object2PosY
	);
	// Load maps array
	void LoadArrayMap(const char* name);
	// Enemy goal
	void ChooseTarget();
	void MoveToTarget();
	void CanSHoot();
	// Spawn upgrade
	void SpawnUpgrade();
	bool CheckSpawnPoss(struct possition elem);
	void CheckSpawnUpgrade(const char* name, powerUps type);
	void InitPossitionUpgrade();
	// Spawm enemy
	tankPreset ChooseType();
	void CheckSpawnEnemy();
	int GetEnemyCount() const {
		return enemyCount;
	}
	void SetEnemyCount(const int enemyCount) {
		this->enemyCount = enemyCount;
	};
	//
	void InitOutOfScreen();
	// Mark
	float GetSpawnEnemyMark() const {
		return spawnEnemyMark;
	}
	void UpdateSpawnEnemyMark(const float mark) {
		spawnEnemyMark += mark;
	};
	void ClearSpawnEnemyMark() {
		spawnEnemyMark = 0.0f;
	};
	bool SpawnPointClear(struct possition enSp);
	// Init fuction
	bool InitSpriteSize();
	void LoadNewMap(const char* nameOfMap);
	void InitAllResources(const char* nameMap, const char* nameLand,
		const int sizeScreenW, const int sizeScreenH);
	// Clear function
	void ClearAllEnemy();
	void ClearUpgrade();
	void ClearLand();
	void CloseProgram();
	// Update function
	bool UpdateTank();
	// Control function
	void PressedKey(FRKey k);
	void ReleasedKey(FRKey k);
	void UpdateMouseClick(FRMouseButton button, bool isReleased);
	void UpdateEnemyTank();
private:
	void Draw();
	void DrawEnemy();
	void DrawUpgrade(const float mark);
	void UpdateHeroTank();
	void PowerUpsColisium();
	void WallHeroColisium();
	bool CheackInitConstructor();
	// Geter
	int GetDifferenceW() const {
		return sizeScreenW - outOfScreenW;
	};
	int GetDifferenceH() const {
		return sizeScreenH - outOfScreenH;
	};
private:
	int sizeScreenW{ 0 };
	int sizeScreenH{ 0 };
	int outOfScreenW{ 0 };
	int outOfScreenH{ 0 };

	int	spawnUpgradePossition{ 0 };
	float spawnExtraLifeTimer{ 0.0f };
	float spawnDrakSidePower{ 0.0f };

	struct enemySpawnTypes enemyUnit {};
	struct possition spawnUpgrade[16];
	struct possition lastUpgradePossiotion {};
	float spawnEnemyMark{ 0.0f };
	unsigned int possition{ 0 };

	int prevHeroKill{ 0 };

	int enemySpawPossition{ 0 };
	float enemyUpdatePossitionMark{ 0.0f };
	float enemyChoosetargetMark{ 0.0f };
	
	int enemyCount{ 20 };
	
	float mark{ 0.0f };
	Map map{};
	Time tm{};
	Hero  hero{};
	Land  land{};
	std::random_device rd;
	std::vector<Enemy> enemy{};
	std::vector<Upgrade> upgrade{};
	int archivePossition{ 0 };
	std::vector<std::string> archiveMap{};
};

