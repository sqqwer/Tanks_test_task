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
	void LoadMap(const char* name, void (*draw)(Sprite*, int, int));
	void DrawMap(float& mark);
private:
	void Draw();

public:
	Block** map = nullptr;
	float mark{ 0 };
private:
	bool isOpen{ false };
	float hsz_x{ 0 };
	float hsz_y{ 0 };
	float monument_x{ 0 };
	float monument_y{ 0 };
	int map_size_w;
	int map_size_h;
	const float animationMark = 0.15f;
};

