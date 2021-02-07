#include "Animation.h"
#include <fstream>
#include <iostream>
#include <string>

Animation::Animation()
{}
// poot path of ini file
Animation::Animation(const char* name, unsigned int range)
	:
	size_of_animation(0), wichOne(0)
{
	if (!LoadPreset(name))
	{
		return;
	}
}
// Load ini file preset
bool Animation::LoadPreset(const char* name)
{
	if (obj.size())
	{
		FreeSprite();
	}
	int i = 0;
	std::string tmp;
	std::ifstream file;
	file.open(name);
	if (!file.is_open())
	{
		std::cout << "Can't open ini file";
		return false;
	}
	while (!file.eof())
	{
		file >> tmp;
		if (tmp[0] == '#') continue;
		Sprite* t = createSprite(tmp.c_str());
		obj.insert(std::pair<int, Sprite*>(i++, t));
	}
	size_of_animation = i--;
	return true;
}
// Animation
Sprite* Animation::Draw(float vellX, float vellY)
{
	wichOne =
		(vellY < 0) ? (wichOne >= (int)anim::FRONT - 1 && wichOne < (int)anim::LEFT - 1)
		? wichOne : (int)anim::FRONT - 1 :
		(vellY > 0) ? (wichOne >= (int)anim::BOTTOM - 1 && wichOne < (int)anim::COUNT - 1)
		? wichOne : (int)anim::BOTTOM - 1 :
		(vellX < 0) ? (wichOne >= (int)anim::LEFT - 1 && wichOne < (int)anim::RIGHT - 1)
		? wichOne : (int)anim::LEFT - 1 :
		(vellX > 0) ? (wichOne >= (int)anim::RIGHT - 1 && wichOne < (int)anim::BOTTOM - 1)
		? wichOne : (int)anim::RIGHT - 1 :
		wichOne;

	if (wichOne >= (int)anim::FRONT - 1 && wichOne < (int)anim::LEFT - 1)
	{
		(wichOne >= (int)anim::LEFT - 2)
			? wichOne = (int)anim::FRONT - 1 :
			(vellY == 0) ? wichOne :
			wichOne++;
		return obj[wichOne];
	}
	if (wichOne >= (int)anim::LEFT - 1 && wichOne < (int)anim::RIGHT - 1)
	{
		(wichOne >= (int)anim::RIGHT - 2)
			? wichOne = (int)anim::LEFT - 1 :
			(vellX == 0) ? wichOne :
			wichOne++;
		return obj[wichOne];
	}
	if (wichOne >= (int)anim::RIGHT - 1 && wichOne < (int)anim::BOTTOM - 1)
	{
		(wichOne >= (int)anim::BOTTOM - 2)
			? wichOne = (int)anim::RIGHT - 1 :
			(vellX == 0) ? wichOne :
			wichOne++;
		return obj[wichOne];
	}
	if (wichOne >= (int)anim::BOTTOM - 1 && wichOne < (int)anim::COUNT - 1)
	{
		(wichOne >= (int)anim::COUNT - 2)
			? wichOne = (int)anim::BOTTOM - 1 :
			(vellY == 0) ? wichOne :
			wichOne++;
		return obj[wichOne];
	}
}
// clear
void Animation::FreeSprite()
{
	for (size_t i = 0; i < size_of_animation; i++)
	{
			destroySprite(obj[i]);
	}
	obj.clear();
}