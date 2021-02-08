#include "Land.h"
#include "Hero.h"
#include "Time.h"
#include "Bullet.h"
#include <iostream>
#include "Framework.h"

/* Test Framework realization */
class MyFramework : public Framework {

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = 800;
		height = 600;
		fullscreen = false;
	}

	virtual bool Init() {
		tm = Time(getTickCount);

		land = Land("land.ini");
		hero = Hero("Hero_model_ver1.ini", "bullet.ini", 1, 200, 200);
		
		if (!land.GetStatus() || !hero.GetStatus())
			return false;		
		getSpriteSize(hero.GetSprite(), hero.GetRefSizeW(), hero.GetRefSizeH());
		return true;
	}

	virtual void Close() {
		hero.FreeSprite();
	}

	virtual bool Tick() {
		const float mark = tm.Mark();	hero.last += mark;
		drawSprite(
			land.GetSprite(), land.GetX(), land.GetY()
		);
		drawSprite(	
			hero.Draw(
			hero.GetvellX(), hero.GetvellY()),
			hero.GetX(), hero.GetY()
		);
		if (hero.bull.size())
		{
			for (int i = 0; i < hero.bull.size(); i++)
			{
				drawSprite(
					hero.bull[i].Draw(
						hero.bull[i].GetvellX(),
						hero.bull[i].GetvellY()
					),
					hero.bull[i].GetX(), 
					hero.bull[i].GetY()
				);
			}
		}

		hero.Update(680, 570, mark);
		
		if (hero.bull.capacity() && !hero.bull.size())
		{
			hero.bull.clear();
			std::vector<Bullet>().swap(hero.bull);
		}
		for (int i = 0; i < hero.bull.size(); i++)
		{
			hero.bull[i].Update(680, 570, mark);
			if (!hero.bull[i].Work())
				hero.ClerBull(i);
		}
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
	Time tm;
	Hero hero;
	Land land;
};

int main(int argc, char* argv[])
{
	return run(new MyFramework);
}
