#pragma once

#include "Framework.h"
#include "Object.h"

class Hero : public Object
{
public:
	Hero();
	Hero(int lives, int poss_x, int poss_y);
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
