#pragma once

#include "Block.h"

enum class Type {
	NOTHING,
	BRICK,
	STEEL,
	WATER,
	LEAAFS,
	MONUMENT,
	HSZ,		// hero spawn zone
	ESZ,		// Enemy spawn zone
	COUNT
};

struct possition {
	possition()  : posX(0.0f), posY(0.0f) {};
	possition(const float posX, const float posY)
		: posX(posX), posY(posY) {};
	bool operator!=(struct possition elem)
	{
		if (posX == elem.posX && posY == elem.posY)
			return false;
		else
			return true;
	};
	float posX;
	float posY;
};

class Map
{
public:
	Map();
	~Map();

	int GetW() const {
		return map_size_w;
	};
	int GetH() const {
		return map_size_h;
	};
	float GetHszX() const {
		return hsz_x;
	};
	float GetHszY() const {
		return hsz_y;
	};
	bool GetStatus() const {
		return isOpen;
	}
	void ClearMemory();
	void AlocateMemory();
	void GetMapSpriteSize();
	void LoadMap(
		const char* name, void (*draw)(Sprite*, int, int),
		const int screenShiftX, const int screenShiftY
	);
	void DrawMap(float& mark);
	// Mark
	void UpdateMark(const float mark) {
		this->mark += mark;
	};
	float& GetRefMark() {
		return mark;
	};
	// Get monument
	float GetMonumentX() const {
		return monument_x;
	};
	float GetMonumentY() const {
		return monument_y;
	};
private:
	void Draw();
public:
	Block** map = nullptr;
	std::vector<possition> enemySpawn{};
private:
	float mark{ 0 };
	bool isOpen{ false };
	float hsz_x{ 0 };
	float hsz_y{ 0 };
	float monument_x{ 0 };
	float monument_y{ 0 };
	int map_size_w;
	int map_size_h;
	const float animationMark = 0.15f;
};

