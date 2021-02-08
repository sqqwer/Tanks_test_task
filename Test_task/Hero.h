#pragma once

#include "Framework.h"
#include "Object.h"
#include "Animation.h"
#include "Bullet.h"

#include <vector>
#include <string>

class Hero : public Object, public Animation
{
public:
	Hero();
	Hero(
		const char* name_ini, const char* bull_preset,
		int lives, int poss_x, int poss_y
	);
	void Shoot();
	void ClerBull(const unsigned int elem);
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
	float out_x;
	float out_y;

	bool live{};
	int	 alives{};
	std::string bull_preset;
	float vellB = 150.0f;
};
