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
		FRONT = 0,
		LEFT = 3,
		RIGHT = 5,
		BOTTOM = 7,
		COUNT = 9
	};
protected:
	int wichOne;
	std::map<int, Sprite*> obj;
private:
	// range of animation
	int size_of_animation;

	//	std::vector<std::vector<Sprite*>> obj;
};

