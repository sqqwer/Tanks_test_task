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
		void (*draw)(Sprite*, int, int), const int type
	);
	int GetType() const {
		return type;
	};
	void SetWich(const int wich) {
		wichOne = wich;
	};
	void Draw();
	void Draw(float& mark);
	enum class type
	{
		BRICK,
		WATER,
		STEEL,
		COUNT
	};
	bool work{false};
private:
	int type{0};
	// initialization virtual function
	void ReleasedKey() {};
	void PressKey(FRKey k) {};
};

