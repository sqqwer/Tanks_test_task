#pragma once

#include <map>
#include "Framework.h"

// Macross define
#define WI(wichOne) wichOne =\
	wichOne = (vellY < 0) ? (wichOne >= sideC[(int)side::FRONT] && wichOne < sideC[(int)side::LEFT])\
		? wichOne : sideC[(int)side::FRONT] :\
	(vellY > 0) ? (wichOne >= sideC[(int)side::BOTTOM] && wichOne < sideC[(int)side::COUNT])\
		? wichOne : sideC[(int)side::BOTTOM] :\
	(vellX < 0) ? (wichOne >= sideC[(int)side::LEFT] && wichOne < sideC[(int)side::RIGHT])\
		? wichOne : sideC[(int)side::LEFT] :\
	(vellX > 0) ? (wichOne >= sideC[(int)side::RIGHT] && wichOne < sideC[(int)side::BOTTOM])\
		? wichOne : sideC[(int)side::RIGHT] : wichOne;

enum class side {
	FRONT = 0,
	LEFT = 1,
	RIGHT = 2,
	BOTTOM = 3,
	COUNT = 4
};

class Animation
{
public:
	Animation();
	Animation(void (*draw)(Sprite*, int, int));
	Animation(const char* name, void (*draw)(Sprite*, int, int));

	virtual void Draw() = 0;

	Sprite* DrawPresset(const float mark, const float animationMark);
	Sprite* GetSprite() {
		return obj[wichOne];
	};
	bool GetStatus() const {
		return isOpen;
	};
	int ShootSide();
	void FreeSprite();
	bool LoadPreset(const char* name);
	Sprite* Choice(float vellX, float vellY);
protected:
	side sd{};
	int wichOne{};
	int sideC[5]{};
	bool isOpen{false};
	int* psideC = sideC;
	unsigned int range{0};
	int size_of_animation{};
protected:
	std::map<int, Sprite*> obj{};
	void (*draw)(Sprite*, int, int){0};
};

