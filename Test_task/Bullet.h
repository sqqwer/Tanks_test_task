#pragma once

#include "Object.h"
#include "Animation.h"

class Bullet : public Animation, public Object
{
public:
	Bullet();
	Bullet(const char* name,
		const float vellX, const float vellY,
		const float possX, const float possY, bool live,
		void (*draw)(Sprite*, int, int)
	);
	void Draw() override;
	void Update(int w, int h, float spec) override;
	void SetWork(const bool w) {
		isWork = w;
	};
	bool Work() const {
		return isWork;
	};
private:
	bool isWork{false};
private:
	// initialization virtual function
	void ReleasedKey() {};
	void PressKey(FRKey k) {};
};