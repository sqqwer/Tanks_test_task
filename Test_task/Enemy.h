#pragma once

#include "Framework.h"
#include "Object.h"
#include "Animation.h"
#include "Bullet.h"

#include <vector>
#include <string>

class Enemy : public Object, public Animation
{
public:
	Enemy();
	Enemy(
		const char* name_ini, const char* bull_preset,
		int lives, int poss_x, int poss_y,
		void (*draw)(Sprite*, int, int)
	);

	void Draw() override;

	void Shoot();
	void UpdateBullet(int screenX, int screenY, float mark);
	void ClerBull(const unsigned int elem);
	void PressKey(FRKey k) {};
	void ReleasedKey() {};
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

