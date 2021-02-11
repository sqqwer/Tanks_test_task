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

class Hero : public Object, public Animation
{
public:
	Hero();
	Hero(tankPreset type,
		const float poss_x, const float poss_y,
		void (*draw)(Sprite*, int, int)
	);
	void Shoot();
	void ClerBull(const unsigned int elem);
	void UpdateBullet(
		int screenX, int screenY, float mark,
		std::vector<Enemy> &en, Map& map
	);
	void TankColisium(
		Enemy& en, const float mark
	);
	void Draw() override;
	void PressKey(FRKey k) override;
	void ReleasedKey() override;
	void ChioceOutShoot();
	
	void Load(tankPreset type);
	// Lives of Tank
	void AddLives(const int health) {
		this->health += health;
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
public:
	std::vector<Bullet> bull{};
private:
	Preset pres;
	float last{ 0.0f };
	float reloadTime{ 0.0f };
	float out_x{ 0.0f };
	float out_y{ 0.0f };
	bool live{ true };
	int	 health{ 1 };
	float speed = 70.0f;;
	float vellB = 250.0f;
};
