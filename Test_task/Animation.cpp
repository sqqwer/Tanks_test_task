#include "Animation.h"
#include <fstream>
#include <iostream>
#include <string>

Animation::Animation()
	:
	wichOne(0)
{};
// poot path of ini file
Animation::Animation(
	const char* name, void (*draw)(Sprite*, int, int)
)
	:
	size_of_animation(0), wichOne(0), draw(draw)
{
	if (!LoadPreset(name))
	{
		return;
	}
};
// Load ini file preset
bool Animation::LoadPreset(const char* name)
{
	if (obj.size())	FreeSprite();
	int i = 0;
	std::string tmp;
	std::ifstream file;
	file.open(name);
	if (file.is_open()) while (!file.eof())
	{
		file >> tmp;
		if (tmp[0] == '#') continue;
		Sprite* t = createSprite(tmp.c_str());
		obj.insert(std::pair<int, Sprite*>(i++, t));
	}
	else
	{
		file.close();
		return (isOpen = false);
	}
	size_of_animation = i--;
	file.close();
	return (isOpen = true);
};
// Choice out frame
Sprite* Animation::Choice(float vellX, float vellY)
{
	WI(wichOne);
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
	return obj[wichOne];
};
// clear sprite map
void Animation::FreeSprite()
{
	for (int i = 0; i < size_of_animation; i++)
	{
		destroySprite(obj[i]);
	}
	obj.clear();
};