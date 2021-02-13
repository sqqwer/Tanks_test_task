#pragma once

#include "Framework.h"

#include "Map.h"
#include "Enemy.h"
#include "Block.h"
#include "Bullet.h"
#include "Preset.h"
#include "Object.h"
#include "Animation.h"

#include <vector>
#include <string>
#include <iostream>

class Hero : public Object, public Animation
{
public:
	Hero();
	Hero(tankPreset type,
		const float poss_x, const float poss_y,
		void (*draw)(Sprite*, int, int),
		const int outOfScreenX, const int outOfScreenY
	);
	void Draw() override;
	void Load(tankPreset type);
	void ClearAllocatedMemory();
	// Colisium
	void TankColisium(Enemy& en, const float mark);
	// Controll
	void ReleasedKey() override;
	void PressKey(FRKey k) override;
	// Shoot funciotn	
	void Shoot(const int outOfScreenX, const int outOfScreenY);
	void UpdateBullet(
		int screenX, int screenY, float mark,
		std::vector<Enemy>& en, Map& map,
		const int outOfScreenX, const int outOfScreenY
	);
	void ChioceOutShoot();
	// Tank Preset
	tankPreset GetTankPreset() const {
		return nowTank;
	};
	void SetTankPreset(const tankPreset type) {
		nowTank = type;
	};
	// Lives of Tank
	void AddLives(const int health) {
		this->health += health;
	}
	int GetHealth() const {
		return health;
	}
	bool isAlive() const {
		return live;
	};
	// Markfunction
	void ClearReloadMark() {
		last = 0;
	};
	float GetReloadMark() const {
		return last;
	};
	void UpdateReloadMark(const float mark) {
		last += mark;
	};
	float GetReloadConstTime() const {
		return reloadTime;
	};
	// speed
	float GetSpeed() const {
		return speed;
	};
	float GetBulletSpeed() const {
		return vellB;
	}
	float GetReloadTime() const {
		return reloadTime;
	};
	// Get Status Data
	void GetInfo() const {
		std::cout << "State information : " << std::endl;
		std::cout << "Health : " << GetHealth() << std::endl;
		std::cout << "Speed : " << GetSpeed() << std::endl;
		std::cout << "Bullet Speed : " << GetBulletSpeed() << std::endl;
		std::cout << "Reload : " << GetReloadTime() << std::endl;
	};
	// Power get and set
	bool GetPower() const {
		return darkSidePower;
	};
	void SetPower(const bool power) {
		darkSidePower = power;
	};
	float GetPowerTimer() const {
		return timer;
	};
	void SetTimer(const float timer) {
		this->timer = timer;
	};
	void TickTimer(const float mark) {
		timer += mark;
	};
	// work with killCount
	void UpdateKillCount(const int iter) {
		killCount += iter;
	}
	int GetKillCount() const {
		return killCount;
	};
	// health
	int& GetRefenceHealth() {
		return health;
	};
	void UpdateLives(const int i) {
		lives += i;
	};
	int GetLives() const {
		return lives;
	};
	void SetLives(const int ls) {
		lives = ls;
	};
private:
	void ClearAllBullet();
	void ClerBull(const unsigned int elem);
public:
	std::vector<Bullet> bull{};
private:
	Preset pres;
	tankPreset nowTank{ tankPreset::COUNT };
	int killCount{ 0 };
	bool  darkSidePower{ false };
	float timer{ 0 };
	float last{ 0.0f };
	float reloadTime{ 0.0f };
	float out_x{ 0.0f };
	float out_y{ 0.0f };

	int lives{ 3 };
	bool live{ true };
	int	 health{ 0 };
	float speed = 70.0f;;
	float vellB = 250.0f;
};
