#pragma once

#include "Framework.h"
#include "Object.h"
#include "Animation.h"

class Hero : public Object, public Animation
{
public:
	Hero();
	Hero(
		const char* name_ini, unsigned int range,
		int lives, int poss_x, int poss_y
	);

	void PressKey(FRKey k) override;
	void ReleasedKey() override;
	void Update(int w, int h, float spec) override;
	
	bool isAlive() const;
	void SetLast(const FRKey k);

	int size_w;
	int size_h;
	FRKey last;
private:
	bool live;
	int	 lives;
};
