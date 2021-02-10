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
	void SetStatus(const side status) {
		this->status = status;
	};
	side GetStatus() const {
		return status;
	};
	void SetPossX(const float addX) {
		possition_x += addX;
	};
	void SetPossY(const float addY) {
		possition_y += addY;
	};
	Sprite* GetWallPoss() {
		return obj[(int)status];
	};
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
	side status{side::COUNT};
	// initialization virtual function
	void ReleasedKey() {};
	void PressKey(FRKey k) {};
};

