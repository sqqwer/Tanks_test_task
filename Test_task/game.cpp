#include "Land.h"
#include "Hero.h"
#include "Time.h"
#include "Bullet.h"
#include "Enemy.h"
#include <string>
#include <iostream>
#include "Framework.h"

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
				const char* str = argv[2];
				char* str_width = new char[10];
				char* str_height = new char[10];
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
				screenX = width = atoi(str_width);
				screenY = height = atoi(str_height);
				delete[] str_width;
				delete[] str_height;
			}
		}
		else
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
		enemy = Enemy("Hero_model_ver1.ini", "bullet.ini", 1, 400, 400, drawSprite);
		if (!land.GetStatus() || !hero.GetStatus())
			return false;
		getSpriteSize(land.GetSprite(), land.GetRefSizeW(), land.GetRefSizeW());
		getSpriteSize(hero.GetSprite(), hero.GetRefSizeW(), hero.GetRefSizeH());
		getSpriteSize(enemy.GetSprite(), enemy.GetRefSizeW(), enemy.GetRefSizeH());

		return true;
	}

	virtual void Close() {
		hero.FreeSprite();
	}

	virtual bool Tick() {
		const float mark = tm.Mark();	
		hero.last += mark; enemy.last += mark;
		land.Draw();	hero.Draw();	enemy.Draw();

		if (enemy.last > 2.25)
		{
			enemy.last = 0;
			enemy.Shoot();
			getSpriteSize(
				enemy.bull[enemy.bull.size() - 1].GetSprite(),
				enemy.bull[enemy.bull.size() - 1].GetRefSizeW(),
				enemy.bull[enemy.bull.size() - 1].GetRefSizeH()
			);
		}
		enemy.UpdateBullet(screenX - 120, screenY - 30, mark);

		hero.Update(screenX - 120, screenY - 30, mark);
		hero.UpdateBullet(screenX - 120, screenY - 30, mark);
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
	int screenX;
	int screenY;

	Time tm;

	Enemy enemy;
	Hero  hero;
	Land  land;
};

int main(int argc, char* argv[])
{
	return run(new MyFramework(&argc, argv));
}
