#pragma once

#include "Framework.h"
#include "Object.h"
#include "Animation.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Block.h"

#include <vector>
#include <string>

class Hero : public Object, public Animation
{
public:
	Hero();
	Hero(
		const char* name_ini, const char* bull_preset,
		int lives, const float poss_x, const float poss_y,
		void (*draw)(Sprite*, int, int)
	);
	void Shoot();
	void ClerBull(const unsigned int elem);
	void UpdateBullet(
		int screenX, int screenY, float mark,
		std::vector<Enemy> &en
	);
	void Draw() override;
	void PressKey(FRKey k) override;
	void ReleasedKey() override;
	void ChioceOutShoot();
	bool isAlive() const {
		return live;
	};
public:
	float last{0};
	std::vector<Bullet> bull{};
private:
	float out_x{};
	float out_y{};

	bool live{};
	int	 alives{};
	std::string bull_preset;
	float vellB = 250.0f;
};
