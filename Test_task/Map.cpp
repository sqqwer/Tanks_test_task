#include "Map.h"

#include <string>
#include <fstream>

Map::Map()
	:
	map_size_w(22), map_size_h(18)
{
	map = new Block * [map_size_h];
	for (int i = 0; i < map_size_h; i++)
	{
		map[i] = new Block[map_size_w];
	};
};

Map::~Map()
{
	for (int i = 0; i < map_size_h; i++)
	{
		for (int j = 0; j < map_size_w; j++)
		{
			map[i][j].FreeSprite();
		}
	}
	for (int i = 0; i < map_size_h; i++)
	{
		delete[] map[i];
	}
	delete[] map;
};

void Map::LoadMap(
	const char* name, void (*draw)(Sprite*, int, int),
	void (*getSize)(Sprite*, int&, int&)
)
{
	std::ifstream file;

	file.open(name);
	
	for (int i = 0; i < map_size_h; i++)
	{
		for (int j = 0; j < map_size_w; j++)
		{
			int k = 0;	file >> k;
			switch (k)
			{
			case (int)Type::NOTHING:
				map[i][j].work = false;
				break;
			case (int)Type::BRICK:
				map[i][j] = Block("block.ini",
					(j + 1) * 30, (i + 1) * 30, draw,
					(int)Type::BRICK
				);
				map[i][j].work = true;
				break;
			case (int)Type::STEEL:
				map[i][j] = Block("steel.ini",
					(j + 1) * 30, (i + 1) * 30, draw,
					(int)Type::STEEL
				);
				map[i][j].work = true;
				break;
			case (int)Type::WATER:
				map[i][j] = Block("water.ini",
					(j + 1) * 30, (i + 1) * 30, draw,
					(int)Type::WATER
				);
				map[i][j].work = true;
				break;
			case (int)Type::LEAAFS:
				map[i][j] = Block("leafs.ini",
					(j + 1) * 30, (i + 1) * 30, draw,
					(int)Type::LEAAFS
				);
				map[i][j].work = true;
				break;
			case (int)Type::MONUMENT:
				map[i][j] = Block("monument.ini",
					(j + 1) * 30, (i + 1) * 30, draw,
					(int)Type::MONUMENT
				);
				map[i][j].work = true;
				break;
			case (int)Type::HSZ:
				hsz_x = (j + 1) * 30;
				hsz_y = (i + 1) * 30;
				map[i][j].work = false;
				break;
			case (int)Type::ESZ:
				map[i][j].work = false;
				break;
			default:
				break;
			}
		}
	}
	file.close();
};

void Map::Draw()
{
	for (int i = 0; i < map_size_h; i++)
	{
		for (int j = 0; j < map_size_w; j++)
		{
			if (map[i][j].work)
				map[i][j].Draw();
		}
	}
};