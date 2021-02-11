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

class Logic
{
public:
	Logic();

	// Check spawn enemy
	void CheckSpawnEnemy();
	// Init fuction
	bool InitSpriteSize();
	void LoadNewMap(const char* nameOfMap);
	void InitAllResources(const char* nameMap, const char* nameLand);
	// Clear function
	void ClearAllEnemy();
	void ClearUpgrade();
	void ClearLand();
	void CloseProgram();
	// Update function
	void UpdateTank(const int screenX, const int screenY);
	// Control function
	void PressedKey(FRKey k);
	void ReleasedKey(FRKey k);
	void UpdateMouseClick(FRMouseButton button, bool isReleased);
private:
	void Draw();
	void DrawUpgrade(const float mark);
	void UpdateHeroTank(const int screenX, const int screenY);
	void UpdateEnemyTank(const int screenX, const int screenY);
	void PowerUpsColisium();
	void WallHeroColisium();
	bool CheackInitConstructor();
private:
	unsigned int possition{ 0 };
	unsigned int enemyCount{ 20 };
	float mark{0.0f};
	Map map{};
	Time tm{};
	Hero  hero{};
	Land  land{};
	std::vector<Enemy> enemy{};
	unsigned int enemyBufeet{0};
	std::vector<Upgrade> upgrade{};
};

