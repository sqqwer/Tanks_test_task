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
	Animation(
		const char* name, void (*draw)(Sprite*, int, int),
		const float posX, const float posY, bool work
	);

	virtual void Draw();
	// Staus of class and frame
	bool GetStatus() const {
		return isOpen;
	};
	// Function to choose out frame
	int ShootSide();
	Sprite* GetSprite() {
		return obj[wichOne];
	};
	Sprite* Choice(float vellX, float vellY);
	Sprite* DrawPresset(const float mark, const float animationMark);
	// Load Free Resource
	void FreeSprite();
	bool LoadPreset(const char* name);
	// Get Poss
	float GetAnimPosX() const {
		return posX;
	};
	float GetAnimPosY() const {
		return posY;
	};
	bool GetWorkUnit() const {
		return work;
	};
	void SetWorkUnit(const bool work) {
		this->work = work;
	};
protected:
	bool work = false;
	float posX{ 0 };
	float posY{ 0 };
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

