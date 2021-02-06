
#include "Framework.h"
#include "Hero.h"
#include "Time.h"
#include <iostream>

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
		/*hero = Hero(createSprite(
			"C:/Users/rozum/source/repos/Test_task/Test_task/data/NES.png"
		), 3, 200, 200);
		*/

		hero = Hero(3, 200, 200);
		getSpriteSize(hero.object[0], hero.size_w, hero.size_h);
		return true;
	}

	virtual void Close() {
		for (int i = 0; i < 2; i++)
		{
			destroySprite(hero.object[i]);
		}
	}

	virtual bool Tick() {
		const float mark = tm.Mark();

		drawTestBackground();
		drawSprite(
			hero.object[(hero.i == 0) ? hero.i = 1: hero.i = 0],
			hero.GetX(), hero.GetY()
		);
		
		hero.Update(1280, 720, mark);
		
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
};

int main(int argc, char* argv[])
{
	return run(new MyFramework);
}
