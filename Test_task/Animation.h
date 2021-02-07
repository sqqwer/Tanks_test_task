#pragma once

#include <map>
#include "Framework.h"

const unsigned int range = 3;

class Animation
{
public:
	Animation();
	Animation(const char* name);
	bool LoadPreset(const char * name);
	Sprite* GetSprite() {
		return obj[wichOne];
	};
	bool GetStatus() const {
		return isOpen;
	}
	Sprite* Draw(float vellX, float vellY);
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
	int wichOne{};
	int size_of_animation{};
	std::map<int, Sprite*> obj{};
};

