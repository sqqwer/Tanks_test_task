#pragma once

#include "Object.h"
#include "Animation.h"

class Block : public Animation, public Object
{
public:
	Block();
	Block(
		const char* name_ini,
		const float possX, const float possY,
		void (*draw)(Sprite*, int, int)
	);
	void Draw() override;
	enum class type
	{
		BRICK,
		WATER,
		STEEL,
		COUNT
	};
private:
	// initialization virtual function
	void ReleasedKey() {};
	void PressKey(FRKey k) {};
};

