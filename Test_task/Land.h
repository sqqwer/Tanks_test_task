#pragma once

#include "Object.h"
#include "Animation.h"

class Land : public Object, public Animation
{
public:
	Land() {};
	Land(const char* name);
	void PressKey(FRKey k) {};
	void ReleasedKey() {};
};