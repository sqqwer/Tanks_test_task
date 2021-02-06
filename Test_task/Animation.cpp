#include "Animation.h"
#include <fstream>
#include <iostream>
#include <string>

Animation::Animation()
{}
// poot path of ini file
Animation::Animation(const char* name, unsigned int range)
	:
	size_of_animation(4), wichOne(0)
{
	std::string tmp;
	std::ifstream file;
	file.open(name);
	if (!file.is_open())
	{
		std::cout << "Can't open ini file";
		return;
	}
	
	file >> size_of_animation;

	for (size_t i = 0; i < size_of_animation; i++)
	{
			file >> tmp;
			Sprite* t = createSprite(tmp.c_str());
			obj.insert(std::pair<int, Sprite*>(i, t));
	}
}
// clear
void Animation::FreeSprite()
{
	for (size_t i = 0; i < size_of_animation; i++)
	{
			destroySprite(obj[i]);
	}
}