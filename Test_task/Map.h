#pragma once

#include "Block.h"

enum class Type {
	NOTHING,
	BRICK,
//	HALFBRICK,
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
	void Draw();
	void LoadMap(
		const char* name, void (*draw)(Sprite*, int, int),
		void (*getSize)(Sprite*, int&, int&)
	);
	float GetHszX() const {
		return hsz_x;
	};
	float GetHszY() const {
		return hsz_y;
	};

public:
	Block** map;
	float mark{0};
private:
	float hsz_x{0};
	float hsz_y{0};
	int map_size_w;
	int map_size_h;
};

