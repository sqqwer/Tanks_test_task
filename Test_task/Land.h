#pragma once

#include "Object.h"
#include "Animation.h"

class Land : public Object, public Animation
{
public:
	Land();
	Land(const char* name, void (*draw)(Sprite*, int, int));
	void Draw() override;
	void ClearLand();
private:
	// initialization virtual function
	void ReleasedKey() {};
	void PressKey(FRKey k) {};
};