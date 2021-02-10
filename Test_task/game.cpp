#include "Map.h"
#include "Land.h"
#include "Hero.h"
#include "Time.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Block.h"
#include "Framework.h"

#include <string>
#include <iostream>

void UpdateBlock(
	Map& map,
	Hero& hero, 
	const float mark
);

void UpdateEnemy(
	std::vector<Enemy>& enemy, Map& map,
	Hero& hero, const float mark,
	const int screenX, const int screenY
);

/* Test Framework realization */
class MyFramework : public Framework {

public:

	MyFramework(int* argc, char* argv[])
		:
		argc(argc), argv(argv), screenX(0), screenY(0)
	{}

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		if (*argc == 3)
		{
			if (!strcmp(argv[1],"-window"))
			{
				char* str_height = NULL;
				char* str_width = NULL;
				const char* str = argv[2];
				str_width = new char[10];
				str_height = new char[10];
				int i = 0, x = 0, s = 0;
				while (str[i] != '\0')
				{
					if (str[i] == 'x')
					{
						x = 1; s = 0; i++;
						continue;
					}
					if (!x)
						str_width[s] = str[i];
					else
						str_height[s] = str[i];
					i++; s++;
				}
				if (str_width || str_height)
				{
					screenX = width = atoi(str_width);
					screenY = height = atoi(str_height);
				}
				delete[] str_width;
				delete[] str_height;
			}
		}
		if ((screenX <= 0 || screenY <= 0))
		{
			width = 800;
			height = 600;
		}
		fullscreen = false;
	}

	virtual bool Init() {
		tm = Time(getTickCount);
		land = Land("land.ini", drawSprite);
		map.LoadMap("Map.ini", drawSprite, getSpriteSize);
		hero = Hero("Hero_model_ver1.ini", "bullet.ini", 1,
			map.GetHszX(), map.GetHszY(), drawSprite
		);
		for (int i = 0; i < map.GetH(); i++)
		{
			for (int j = 0; j < map.GetW(); j++)
			{
				if (map.map[i][j].work) {
					getSpriteSize( 
						map.map[i][j].GetWallPoss(),
						map.map[i][j].GetRefSizeW(),
						map.map[i][j].GetRefSizeH()
					);
				}
			}
		}
	
		float x = 10.0f;
		float y = 50.0f;
		for (int i = 0; i < 10; i++)
		{
			enemy.push_back(Enemy((i % 2 == 0) ? "Hero_model_ver1.ini" : "Hero_model.ini", 
				"bullet.ini", 1, x, y, drawSprite));
			if (i % 2 == 0) enemy[i].SetVellX(70.0f); else enemy[i].SetVellY(100.0f);
			getSpriteSize(enemy[i].GetSprite(), enemy[i].GetRefSizeW(), enemy[i].GetRefSizeH());
			x += 40; y += 40;
		}
		if (!land.GetStatus() || !hero.GetStatus())
			return false;
		getSpriteSize(land.GetSprite(), land.GetRefSizeW(), land.GetRefSizeW());
		getSpriteSize(hero.GetSprite(), hero.GetRefSizeW(), hero.GetRefSizeH());

		return true;
	}

	virtual void Close() {
		hero.FreeSprite();
		land.FreeSprite();
		/*for (int i = 0; i < block.size(); i++) {
			block[i].FreeSprite();
		}*/
		for (int i = 0; i < enemy.size(); i++) {
			enemy[i].FreeSprite();
		}
		_CrtDumpMemoryLeaks();
	}

	virtual bool Tick() {
		const float mark = tm.Mark();	
		hero.last += mark;	map.mark += mark;
		land.Draw();	hero.Draw();
		hero.Update(screenX - 120, screenY - 30, mark);
		UpdateBlock(map, hero, mark);
		hero.UpdateBullet(screenX - 120, screenY - 30, mark, enemy, map);
		UpdateEnemy(enemy, map, hero, mark, screenX, screenY);

		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {

	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		if (
			button == FRMouseButton::LEFT && isReleased
			&& hero.last > 0.25 // reload of shoot
			)
		{
			hero.last = 0;
			hero.Shoot();
			getSpriteSize(
				hero.bull[hero.bull.size() - 1].GetSprite(),
				hero.bull[hero.bull.size() - 1].GetRefSizeW(),
				hero.bull[hero.bull.size() - 1].GetRefSizeH()
			);
		}
	}

 	virtual void onKeyPressed(FRKey k) {	
		hero.PressKey(k);
	}

	virtual void onKeyReleased(FRKey k) {
		hero.ReleasedKey();
	}

	virtual const char* GetTitle() override
	{
		return "Tanks";
	}

private:
int* argc;
char** argv;
float amark{ 0 };
int screenX = 0;
int screenY = 0;

Time tm;
Hero  hero;
Land  land;

Map map;
std::vector<Enemy> enemy;
};

int main(int argc, char* argv[])
{
	return run(new MyFramework(&argc, argv));
}

void UpdateEnemy(
	std::vector<Enemy>& enemy, Map& map,
	Hero& hero, const float mark,
	const int screenX, const int screenY
)
{
	for (int i = 0; i < enemy.size(); i++)
	{
		enemy[i].UpdateBullet(screenX - 120, screenY - 30, mark, enemy, map, i);
		if (enemy[i].isAlive())
		{
			enemy[i].last += mark;
			enemy[i].Update(screenX - 120, screenY - 30, mark);
			enemy[i].Draw();
			if (enemy[i].last > 5)
			{
				if (enemy[i].last > 3.5 && !enemy[i].GetvellX() && !enemy[i].GetvellY())
				{
					enemy[i].SetVellX(70.0f);
				}
				enemy[i].last = 0;	enemy[i].Shoot();
				getSpriteSize(
					enemy[i].bull[enemy[i].bull.size() - 1].GetSprite(),
					enemy[i].bull[enemy[i].bull.size() - 1].GetRefSizeW(),
					enemy[i].bull[enemy[i].bull.size() - 1].GetRefSizeH()
				);
			}
			hero.Hero::TankColisium(enemy[i], mark);
			for (int j = 0; j < enemy.size(); j++)
			{
				if (i != j && (enemy[i].isAlive() && enemy[j].isAlive()))
					enemy[i].Enemy::TankColisium(
						(float)enemy[j].GetX(), (float)enemy[j].GetY(),
						(float)enemy[j].GetSpW(), (float)enemy[j].GetSpH(), mark
					);
			}
			for (int k = 0; k < map.GetH(); k++)
			{

				for (int j = 0; j < map.GetW(); j++)
				{
					if (map.map[k][j].work && enemy[i].isAlive() &&
						(int)Type::LEAAFS != map.map[k][j].GetType())
					{
						enemy[i].Enemy::Colisium(
							(float)map.map[k][j].GetX(),
							(float)map.map[k][j].GetY(),
							(float)map.map[k][j].GetSpW(),
							(float)map.map[k][j].GetSpH(), mark
						);
					}
				}
			}
		}
		else if (!enemy[i].isAlive() && !enemy[i].bull.size() &&
			!enemy[i].bull.capacity())
		{
			enemy[i].FreeSprite();
			enemy.erase(enemy.begin() + i);
		}
	}
	if (enemy.capacity() && !enemy.size())
	{
		enemy.shrink_to_fit();
	}
};

void UpdateBlock(
	Map& map,
	Hero& hero, const float mark
)
{
	for (int i = 0; i < map.GetH(); i++)
	{
		for (int j = 0; j < map.GetW(); j++)
		{
			if (map.map[i][j].work)
			{
				if (
					(int)Type::LEAAFS == map.map[i][j].GetType() ||
					(int)Type::MONUMENT == map.map[i][j].GetType() ||
					(int)Type::WATER == map.map[i][j].GetType()
					)
				{
					map.map[i][j].Block::Draw(map.mark);
				}
				else
				{
					map.map[i][j].Block::Draw();
				}
				if ((int)Type::LEAAFS != map.map[i][j].GetType())
				{
					hero.Object::Colisium(
						(float)map.map[i][j].GetX(),
						(float)map.map[i][j].GetY(),
						(float)map.map[i][j].GetSpW(),
						(float)map.map[i][j].GetSpH(),
						mark
					);
				}
			}
		}
	}
	if (map.mark > 0.15f) map.mark = 0;
};