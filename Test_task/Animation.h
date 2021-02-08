#pragma once

#include <map>
#include "Framework.h"

const unsigned int range = 3;
// Macross define
#define WI(wichOne) wichOne =\
	(vellY < 0) ? (wichOne >= (int)anim::FRONT - 1 && wichOne < (int)anim::LEFT - 1)\
	? wichOne : (int)anim::FRONT - 1 : (vellY > 0)\
	? (wichOne >= (int)anim::BOTTOM - 1 && wichOne < (int)anim::COUNT - 1)\
	? wichOne : (int)anim::BOTTOM - 1 : (vellX < 0)\
	? (wichOne >= (int)anim::LEFT - 1 && wichOne < (int)anim::RIGHT - 1)\
	? wichOne : (int)anim::LEFT - 1 : (vellX > 0)\
	? (wichOne >= (int)anim::RIGHT - 1 && wichOne < (int)anim::BOTTOM - 1)\
	? wichOne : (int)anim::RIGHT - 1 : wichOne;
#define WICH_SIDE(sd) sd = \
	(wichOne >= (int)anim::FRONT - 1 && wichOne < (int)anim::LEFT - 1) ? side::FRONT :\
	(wichOne >= (int)anim::LEFT - 1 && wichOne < (int)anim::RIGHT - 1) ? side::LEFT : \
	(wichOne >= (int)anim::RIGHT - 1 && wichOne < (int)anim::BOTTOM - 1) ? side::RIGHT :\
	(wichOne >= (int)anim::BOTTOM - 1 && wichOne < (int)anim::COUNT - 1) ? side::BOTTOM : sd;

enum class side
{
	FRONT,
	BOTTOM,
	LEFT,
	RIGHT,
	COUNT
};

class Animation
{
public:
	Animation();
	Animation(
		const char* name, void (*draw)(Sprite*, int, int)
	);
	bool LoadPreset(const char * name);
	Sprite* GetSprite() {
		return obj[wichOne];
	};
	bool GetStatus() const {
		return isOpen;
	}
	virtual void Draw() = 0;
	Sprite* Choice(float vellX, float vellY);
	void FreeSprite();

	enum class anim
	{
		FRONT = 1,
		LEFT = FRONT + range,
		RIGHT = LEFT + range,
		BOTTOM = RIGHT + range,
		COUNT = BOTTOM + range
	};
protected:
	bool isOpen{false};
	side sd {};
	int wichOne{};
	int size_of_animation{};

	void (*draw)(Sprite*, int, int) {};
	std::map<int, Sprite*> obj{};
};

