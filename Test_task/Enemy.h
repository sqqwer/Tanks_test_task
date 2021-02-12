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

class Enemy : public Object, public Animation
{
public:
	Enemy();
	Enemy(tankPreset type,
		const float poss_x, const float poss_y,
		void (*draw)(Sprite*, int, int),
		const int outOfScreenX, const int outOfScreenY
	);
	void Draw() override;
	void Load(tankPreset type);
	void ClearAllocatedMemory();
	// Colisium function
	void Colisium(
		const float possX, const float possY,
		const float width, const float height,
		const float mark, const int magicNumber
	);
	void TankColisium(
		const float possX, const float possY,
		const float width, const float height,
		const float mark, const int magicNumber
	);
	// Shoot Function
	void Shoot(const int outOfScreenX, const int outOfScreenY);
	void UpdateBullet(
		int screenX, int screenY, float mark,
		std::vector<Enemy>& en,
		Map& map, const int wich,
		const int outOfScreenX, const int outOfScreenY
	);
	void ChioceOutShoot();
	// Update possition
	void Update(int w, int h, float spec,
		const int outOfScreenX, const int outOfScreenY
	);
	// Tank Preset
	tankPreset GetTankPreset() const {
		return nowTank;
	};
	void SetTankPreset(const tankPreset type) {
		nowTank = type;
	};
	// Lives
	bool isAlive() const {
		return live;
	};
	void SetLive(const bool l) {
		live = l;
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
	// Target
	int GetTarget() const {
		return enemyTarget;
	};
	void SetTraget(const int target) {
		enemyTarget = target;
	};
private:
	void ClearAllBullet();
	void ClerBull(const unsigned int elem);
	// Not used virtual function
	void ReleasedKey() {};
	void PressKey(FRKey k) {};
public:
	std::vector<Bullet> bull{};
private:
	Preset pres;
	tankPreset nowTank{ tankPreset::COUNT };
	int enemyTarget{ 0 };
	float last{ 0.0f };
	float reloadTime{ 0.0f };
	bool live{ true };
	int	 health{ 1 };
	float out_x{ 0.0f };
	float out_y{ 0.0f };
	float speed = 70.0f;;
	float vellB = 250.0f;
};

