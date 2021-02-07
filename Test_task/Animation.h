#pragma once

#include <map>
#include "Framework.h"

const unsigned int range = 3;

class Animation
{
public:
	Animation();
	Animation(const char* name, unsigned int range);
	
	bool LoadPreset(const char * name);
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
	int wichOne;
	std::map<int, Sprite*> obj;
	int size_of_animation;
};

