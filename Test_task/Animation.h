#pragma once

#include <map>
#include "Framework.h"

const unsigned int range = 2;

class Animation
{
public:
	Animation();
	Animation(const char* name, unsigned int range);
	virtual Sprite* Draw(float vellX, float vellY) = 0;
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
private:
	// range of animation
	int size_of_animation;

	//	std::vector<std::vector<Sprite*>> obj;
};

