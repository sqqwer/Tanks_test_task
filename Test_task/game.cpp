#include "Land.h"
#include "Hero.h"
#include "Time.h"
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
		hero = Hero("Hero_model_ver1.ini", 1, 200, 200);
		if (!land.GetStatus() || !hero.GetStatus())
			return false;		
		getSpriteSize(hero.Draw(0.0f, 0.0f),
			hero.GetRefSizeW(),
			hero.GetRefSizeH()
		);
		return true;
	}

	virtual void Close() {
		hero.FreeSprite();
	}

	virtual bool Tick() {
		const float mark = tm.Mark();
	/*	if (hero.GetX() > 300)
		{
			hero.LoadPreset("Hero_model.ini");
		}
		else if (hero.GetX() < 300)
		{
			hero.LoadPreset("Hero_model_ver1.ini");
		}*/
		drawSprite(
			land.GetSprite(), land.GetX(), land.GetY()
		);
		drawSprite(	
			hero.Draw(
			hero.GetvellX(), hero.GetvellY()),
			hero.GetX(), hero.GetY()
		);
		hero.Update(680, 570, mark);
		
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {

	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {

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
