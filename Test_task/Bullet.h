#pragma once

#include "Object.h"
#include "Animation.h"

class Bullet : public Animation, public Object
{
public:
	Bullet() {};
	Bullet(const char* name,
		const float vellX, const float vellY,
		const float possX, const float possY, bool live,
		void (*draw)(Sprite*, int, int)
	);

	void Draw() override;
	void Update(int w, int h, float spec) override;
	bool Work() const {
		return isWork;
	};
	// initialization virtual function
	void ReleasedKey() {};
	void PressKey(FRKey k) {};
private:
	bool isWork{false};
};