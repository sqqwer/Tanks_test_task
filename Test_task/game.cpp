#include "Framework.h"

#include "Logic.h"

/* Test Framework realization */
class MyFramework : public Framework {

public:

	MyFramework(int* argc, char* argv[])
		:
		argc(argc), argv(argv), screenX(0), screenY(0)
	{}

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		screenX = screenY = 0;
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
		if (screenY <= 0 || screenY < 600)
		{
			screenY = height = 600;
		}
		if (screenX <= 0 || screenY < 800)
		{
			screenX = width = 800;
		}

		fullscreen = false;
	}

	virtual bool Init() {
		logic.InitAllResources(
			"./data/map/allMap.ini", "./data/land/land.ini",
			screenX, screenY
		);	
		if (!logic.InitSpriteSize())
			return false;
		return true;
	}

	virtual void Close() {
		logic.CloseProgram();
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		_CrtSetBreakAlloc(9554);
		_CrtSetBreakAlloc(9553);
		_CrtSetBreakAlloc(9552);
	}

	virtual bool Tick() {
		logic.UpdateTank();
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {

	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		logic.UpdateMouseClick(button, isReleased);
	}

 	virtual void onKeyPressed(FRKey k) {	
		logic.PressedKey(k);
	}

	virtual void onKeyReleased(FRKey k) {
		logic.ReleasedKey(k);
	}

	virtual const char* GetTitle() override {
		return "Tanks";
	}

private:
int* argc;
char** argv;
int screenX;
int screenY;
Logic logic{};
};

int main(int argc, char* argv[])
{
	return run(new MyFramework(&argc, argv));
};