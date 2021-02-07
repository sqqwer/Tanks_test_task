#pragma once

#include "Framework.h"
#include "Object.h"
#include "Animation.h"

class Hero : public Object, public Animation
{
public:
	Hero();
	Hero(
		const char* name_ini,
		int lives, int poss_x, int poss_y
	);
	void PressKey(FRKey k) override;
	void ReleasedKey() override;
	bool isAlive() const {
		return live;
	};
private:
	bool live{};
	int	 alives{};
};
