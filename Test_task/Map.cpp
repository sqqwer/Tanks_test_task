#include "Map.h"

#include <string>
#include <fstream>

Map::Map()
	:
	map_size_w(23), map_size_h(18)
{
	AlocateMemory();
};

Map::~Map()
{
	ClearMemory();
};

void Map::ClearMemory()
{
	enemySpawn.clear();
	for (int i = 0; i < map_size_h; i++)
	{
		for (int j = 0; j < map_size_w; j++)
		{
			for (int k = 0; k < map[i][j].unit.size(); k++)
			{
				if (map[i][j].unit[k].Animation::GetStatus())
					map[i][j].unit[k].FreeSprite();
			}
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
				for (int k = 0; k < map[i][j].unit.size(); k++) {

					getSpriteSize(map[i][j].unit[k].GetSprite(), map[i][j].GetRefSizeW(),
						map[i][j].GetRefSizeH()
					);
				}
			}
		}
	}
};

void Map::LoadMap(const char* name, void (*draw)(Sprite*, int, int),
	const int screenShiftX, const int screenShiftY
)
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
					map[i][j] = Block("./data/block/brick/BLK.ini",
						(float)(screenShiftX + (j) * 30),
						(float)(screenShiftY + (i) * 30),
						(int)Type::BRICK, true
					);
					map[i][j].SetLiveBlock(true);
					break;
				case (int)Type::STEEL:
					map[i][j].SetStatus(side::COUNT);
					map[i][j] = Block("./data/block/steel/SBL.ini",
						(float)(screenShiftX + (j) * 30),
						(float)(screenShiftY + (i) * 30),
						(int)Type::STEEL, true
					);
					map[i][j].SetLiveBlock(true);
					break;
				case (int)Type::WATER:
					map[i][j].SetStatus(side::COUNT);
					map[i][j] = Block("./data/block/water/water.ini",
						(float)(screenShiftX + (j) * 30),
						(float)(screenShiftY + (i) * 30),
						(int)Type::WATER, false
					);
					map[i][j].SetLiveBlock(true);
					break;
				case (int)Type::LEAAFS:
					map[i][j].SetStatus(side::COUNT);
					map[i][j] = Block("./data/block/leafs/leafs.ini",
						(float)(screenShiftX + (j) * 30),
						(float)(screenShiftY + (i) * 30),
						(int)Type::LEAAFS, false
					);
					map[i][j].SetLiveBlock(true);
					break;
				case (int)Type::MONUMENT:
					SetMonumentLive(true);
					map[i][j].SetStatus(side::COUNT);
					map[i][j].SetLiveBlock(true);
					map[i][j] = Block("./data/block/monument/monument.ini",
						(float)(screenShiftX + (j) * 30),
						(float)(screenShiftY + (i) * 30),
						(int)Type::MONUMENT, false
					);
					monX = j; monY = i;
					monument_x = (float)(screenShiftX + (j) * 30);
					monument_y = (float)(screenShiftY + (i) * 30);
					map[i][j].SetLiveBlock(true);
					break;
				case (int)Type::HSZ:
					map[i][j].SetStatus(side::COUNT);
					hsz_x = (float)(screenShiftX + (j) * 30);
					hsz_y = (float)(screenShiftY + (i) * 30);
					map[i][j].SetLiveBlock(false);
					break;
				case (int)Type::ESZ:
					map[i][j].SetLiveBlock(false);
					enemySpawn.push_back(
						possition(
							(float)(screenShiftX + (j) * 30),
							(float)(screenShiftY + (i) * 30))
					);
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
			{
				map[i][j].Draw();
			}
		}
	}
};

void Map::DrawMap(float& mark)
{
	for (int i = 0; i < GetH(); i++)
	{
		for (int j = 0; j < GetW(); j++)
		{
			for (int k = 0; k < map[i][j].unit.size(); k++)
			{
				if (map[i][j].unit[k].GetWorkUnit())
				{
					if (
						(int)Type::LEAAFS == map[i][j].GetType() ||
						(int)Type::MONUMENT == map[i][j].GetType() ||
						(int)Type::WATER == map[i][j].GetType()
						)
					{
						drawSprite(map[i][j].unit[k].DrawPresset(mark, animationMark),
							(int)map[i][j].unit[k].GetAnimPosX(), (int)map[i][j].unit[k].GetAnimPosY());
					}
					else if (
						(int)Type::BRICK == map[i][j].GetType() ||
						(int)Type::STEEL == map[i][j].GetType())
					{
						drawSprite(map[i][j].unit[k].GetSprite(), 
							(int)map[i][j].unit[k].GetAnimPosX(), (int)map[i][j].unit[k].GetAnimPosY());
					}
				}
			}
		}
	}
	if (mark > animationMark) mark = 0;
};