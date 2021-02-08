#pragma once

#include "Object.h"
#include "Animation.h"

class Bullet : public Animation, public Object
{
public:
	Bullet() {};
	Bullet(const char* name,
		const float vellX, const float vellY,
		const float possX, const float possY, bool live
	);
	bool Work() const {
		return isWork;
	};
	void Update(int w, int h, float spec) override;
	// initialization virtual function
	void ReleasedKey() {};
	void PressKey(FRKey k) {};
private:
	bool isWork{false};
};

