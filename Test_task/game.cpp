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
	std::vector<Block>& block,
	Hero& hero, const float mark
);

void UpdateEnemy(
	std::vector<Enemy>& enemy,
	std::vector<Block>& block,
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
				char* str_height = nullptr;
				char* str_width = nullptr;
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
		hero = Hero("Hero_model_ver1.ini", "bullet.ini", 1, 200, 200, drawSprite);

		float b_x = 300.0f;
		float b_y = 200.0f;
		for (int i = 0; i < 5; i++)
		{
			block.push_back(Block("block.ini", b_x, b_y, drawSprite));
			getSpriteSize(block[i].GetSprite(), block[i].GetRefSizeW(), block[i].GetRefSizeH());
			b_x += 30;
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
		for (int i = 0; i < block.size(); i++) {
			block[i].FreeSprite();
		}
		for (int i = 0; i < enemy.size(); i++) {
			enemy[i].FreeSprite();
		}
		_CrtDumpMemoryLeaks();
	}

	virtual bool Tick() {
		const float mark = tm.Mark();	hero.last += mark;
		land.Draw();	hero.Draw();	
		hero.Update(screenX - 120, screenY - 30, mark);
		UpdateBlock(block, hero, mark);
		hero.UpdateBullet(screenX - 120, screenY - 30, mark, enemy, block);
		UpdateEnemy(enemy, block, hero, mark, screenX, screenY);

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
	int screenX = 0;
	int screenY = 0;

	Time tm;
	Hero  hero;
	Land  land;

	std::vector<Block> block;
	std::vector<Enemy> enemy;
};

int main(int argc, char* argv[])
{
	return run(new MyFramework(&argc, argv));
}

void UpdateEnemy(
	std::vector<Enemy>& enemy,
	std::vector<Block>& block,
	Hero& hero, const float mark,
	const int screenX, const int screenY
)
{
	for (int i = 0; i < enemy.size(); i++)
	{
		enemy[i].UpdateBullet(screenX - 120, screenY - 30, mark, enemy, block, i);
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
				if (i != j)
					enemy[i].Enemy::TankColisium(
						(float)enemy[j].GetX(), (float)enemy[j].GetY(),
						(float)enemy[j].GetSpW(), (float)enemy[j].GetSpH(), mark
					);
			}
			for (int j = 0; j < block.size(); j++)
			{
				enemy[i].Enemy::Colisium(
					(float)block[j].GetX(), (float)block[j].GetY(),
					(float)block[j].GetSpW(), (float)block[j].GetSpH(), mark
				);
			}
		}
		else if (
			!enemy[i].isAlive() && !enemy[i].bull.size() && !enemy[i].bull.capacity()
			)
		{
			enemy[i].FreeSprite();
			enemy.erase(enemy.begin() + i);
		}
	}
	if (enemy.capacity() && !enemy.size())
	{
		enemy.shrink_to_fit();
	}
}

void UpdateBlock(
	std::vector<Block>& block,
	Hero& hero, const float mark
)
{
	for (int i = 0; i < block.size(); i++)
	{
		block[i].Draw();
	}
	for (int i = 0; i < block.size(); i++)
	{
		hero.Colisium(
			(float)block[i].GetX(), (float)block[i].GetY(),
			(float)block[i].GetSpW(), (float)block[i].GetSpH(), mark
		);
	}
}