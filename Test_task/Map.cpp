#include "Map.h"

#include <string>
#include <fstream>

Map::Map()
	:
	map_size_w(22), map_size_h(18)
{
	AlocateMemory();
};

Map::~Map()
{
	ClearMemory();
};

void Map::ClearMemory()
{
	for (int i = 0; i < map_size_h; i++)
	{
		for (int j = 0; j < map_size_w; j++)
		{
			if (map[i][j].Animation::GetStatus())
				map[i][j].FreeSprite();
		}
	}
	for (int i = 0; i < map_size_h; i++)
	{
		delete[] map[i];
	}
	delete[] map;
};

void Map::AlocateMemory()
{
	map = new Block * [map_size_h];
	for (int i = 0; i < map_size_h; i++)
	{
		map[i] = new Block[map_size_w];
	};
};

void Map::GetMapSpriteSize()
{
	for (int i = 0; i < GetH(); i++)
	{
		for (int j = 0; j < GetW(); j++)
		{
			if (map[i][j].GetLiveBlock()) {
				getSpriteSize(map[i][j].GetWallPoss(), map[i][j].GetRefSizeW(),
					map[i][j].GetRefSizeH()
				);
			}
		}
	}
};

void Map::LoadMap(const char* name, void (*draw)(Sprite*, int, int))
{
	std::ifstream file;
	file.open(name);
	if (file.is_open())
	{
		for (int i = 0; i < map_size_h; i++)
		{
			for (int j = 0; j < map_size_w; j++)
			{
				int k = 0;	file >> k;
				switch (k)
				{
				case (int)Type::NOTHING:
					map[i][j].SetLiveBlock(false);
					break;
				case (int)Type::BRICK:
					map[i][j].SetStatus(side::COUNT);
					map[i][j] = Block("block.ini",
						(float)((j + 1) * 30),
						(float)((i + 1) * 30),
						draw, (int)Type::BRICK
					);
					map[i][j].SetLiveBlock(true);
					break;
				case (int)Type::STEEL:
					map[i][j].SetStatus(side::COUNT);
					map[i][j] = Block("steel.ini",
						(float)((j + 1) * 30),
						(float)((i + 1) * 30),
						draw, (int)Type::STEEL
					);
					map[i][j].SetLiveBlock(true);
					break;
				case (int)Type::WATER:
					map[i][j].SetStatus(side::COUNT);
					map[i][j] = Block("water.ini",
						(float)((j + 1) * 30),
						(float)((i + 1) * 30),
						draw, (int)Type::WATER
					);
					map[i][j].SetLiveBlock(true);
					break;
				case (int)Type::LEAAFS:
					map[i][j].SetStatus(side::COUNT);
					map[i][j] = Block("leafs.ini",
						(float)((j + 1) * 30),
						(float)((i + 1) * 30),
						draw, (int)Type::LEAAFS
					);
					map[i][j].SetLiveBlock(true);
					break;
				case (int)Type::MONUMENT:
					map[i][j].SetStatus(side::COUNT);
					map[i][j] = Block("monument.ini",
						(float)((j + 1) * 30),
						(float)((i + 1) * 30),
						draw, (int)Type::MONUMENT
					);
					map[i][j].SetLiveBlock(true);
					break;
				case (int)Type::HSZ:
					map[i][j].SetStatus(side::COUNT);
					hsz_x = (float)((j + 1) * 30);
					hsz_y = (float)((i + 1) * 30);
					map[i][j].SetLiveBlock(false);
					break;
				case (int)Type::ESZ:
					map[i][j].SetLiveBlock(false);
					break;
				default:
					break;
				}
			}
		}
	}
	else
	{
		isOpen = false;
	}
	isOpen = true;
	file.close();
};

void Map::Draw()
{
	for (int i = 0; i < map_size_h; i++)
	{
		for (int j = 0; j < map_size_w; j++)
		{
			if (map[i][j].GetLiveBlock())
				map[i][j].Draw();
		}
	}
};

void Map::DrawMap(float& mark)
{
	for (int i = 0; i < GetH(); i++)
	{
		for (int j = 0; j < GetW(); j++)
		{
			if (map[i][j].GetLiveBlock())
			{
				if (
					(int)Type::LEAAFS == map[i][j].GetType() ||
					(int)Type::MONUMENT == map[i][j].GetType() ||
					(int)Type::WATER == map[i][j].GetType()
					)
				{
					map[i][j].Block::Draw(mark, animationMark);
				}
				else
				{
					map[i][j].Block::Draw();
				}
			}
		}
	}
	if (mark > animationMark) mark = 0;
};