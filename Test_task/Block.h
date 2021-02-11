#pragma once

#include "Object.h"
#include "Animation.h"

#include <vector>

class Block : public Object
{
public:
	Block();
	Block(
		const char* name_ini, const float possX, 
		const float possY, const int type, bool triger
	);
	void ClearBlock();
	// Draw function
	void Draw();
	void DrawBrick();
	void Draw(const float mark, const float animationMark);
	void SetStatus(const side status) {
		this->status = status;
	};
	// Geter
	int GetType() const {
		return type;
	};
	side GetStatus() const {
		return status;
	};
	//Sprite* GetWallPoss() {
	//	return obj[(int)status];
	//};
	//// Seter
	//void SetWich(const int wich) {
	//	wichOne = wich;
	//};
	void SetPossX(const float addX) {
		possition_x += addX;
	};
	void SetPossY(const float addY) {
		possition_y += addY;
	};
	// Enum constant
	enum class type
	{
		BRICK,
		WATER,
		STEEL,
		COUNT
	};
	// work with work block
	bool GetLiveBlock() const {
		return blockLive;
	};
	void SetLiveBlock(const bool blockLive) {
		this->blockLive = blockLive;
	}
public:
	std::vector<Animation> unit{};
private:
	// initialization virtual function
	void ReleasedKey() {};
	void PressKey(FRKey k) {};
private:
	int type{0};
	bool blockLive{ false };
	
	side status{side::COUNT};
};

