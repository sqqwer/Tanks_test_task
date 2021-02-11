#include "Preset.h"

#include <string>
#include <fstream>

Preset::Preset()
{};


void Preset::LoadPreset(tankPreset type)
{
	std::ifstream file;
	this->type = type;

	switch (type)
	{
	case tankPreset::HEROTANK1:
		ReadFile("Hero_preset.ini");
		break;
	case tankPreset::HEROTANK2:
		break;
	case tankPreset::HEROTANK3:
		break;
	case tankPreset::ENEMYTANKEASY:
		break;
	case tankPreset::ENEMYTANKFAST:
		break;
	case tankPreset::ENEMYTANKPOWER:
		break;
	case tankPreset::ENEMYTANKARMOR:
		break;
	case tankPreset::WIDTHTANK:
		ReadFile("WidthTank.ini");
		break;
	case tankPreset::COUNT:
		break;
	default:
		break;
	}
};

void Preset::ReadFile(const char* name)
{

	std::ifstream file;
	file.open(name);
	if (file.is_open())
	{
		file >> health;
		file >> tank_velocity;
		file >> bullet_velocity;
		file >> bullet_reload;
		file >> animationTankPreset;
		file >> animationBulletPreset;
	}
	file.close();
};