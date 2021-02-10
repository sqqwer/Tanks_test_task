#include "Animation.h"

#include <string>
#include <fstream>
#include <iostream>

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

int Animation::ShootSide()
{
	return (
		(wichOne >= sideC[(int)side::FRONT] && wichOne < sideC[(int)side::LEFT])
		? (int)side::FRONT :
		(wichOne >= sideC[(int)side::LEFT] && wichOne < sideC[(int)side::RIGHT])
		? (int)side::LEFT :
		(wichOne >= sideC[(int)side::RIGHT] && wichOne < sideC[(int)side::BOTTOM])
		? (int)side::RIGHT :
		(wichOne >= sideC[(int)side::BOTTOM] && wichOne < sideC[(int)side::COUNT])
		? (int)side::BOTTOM : (int)sd
	);
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
	size_of_animation = i;
	range = i / 4;
	sideC[0] = 0;
	for (int i = 1; i < 5; i++)
	{
		sideC[i] = sideC[i - 1] + range;
	}
	file.close();
	return (isOpen = true);
};
// Choice out frame
Sprite* Animation::Choice(float vellX, float vellY)
{
	WI(wichOne);
	if (wichOne >= sideC[(int)side::FRONT] && wichOne < sideC[(int)side::LEFT])
	{
		(wichOne >= sideC[(int)side::LEFT] - 1) ? wichOne = sideC[(int)side::FRONT] :
			(vellY == 0) ? wichOne : wichOne++;
		return obj[wichOne];
	}
	if (wichOne >= sideC[(int)side::LEFT] && wichOne < sideC[(int)side::RIGHT])
	{
		(wichOne >= sideC[(int)side::RIGHT] - 1) ? wichOne = sideC[(int)side::LEFT] :
			(vellX == 0) ? wichOne : wichOne++;
		return obj[wichOne];
	}
	if (wichOne >= sideC[(int)side::RIGHT] && wichOne < sideC[(int)side::BOTTOM])
	{
		(wichOne >= sideC[(int)side::BOTTOM] - 1) ? wichOne = sideC[(int)side::RIGHT]:
			(vellX == 0) ? wichOne : wichOne++;
		return obj[wichOne];
	}
	if (wichOne >= sideC[(int)side::BOTTOM] && wichOne < sideC[(int)side::COUNT])
	{
		(wichOne >= sideC[(int)side::COUNT] - 1) ? wichOne = sideC[(int)side::BOTTOM] :
			(vellY == 0) ? wichOne : wichOne++;
		return obj[wichOne];
	}
	return obj[wichOne];
};
// clear sprite map
void Animation::FreeSprite()
{
	if (!obj.empty())
	{
		for (int i = 0; i < size_of_animation; i++)
		{
			destroySprite(obj[i]);
			obj.erase(i);
		}
		std::map<int, Sprite*>().swap(obj);
	}
};
// Draw Presset
Sprite* Animation::DrawPresset(float& mark)
{
	if (mark > 0.10f) wichOne++;
	if (wichOne >= obj.size()) wichOne = 0;
	return obj[wichOne];
};