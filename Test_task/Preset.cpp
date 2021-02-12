#include "Preset.h"

#include <string>
#include <fstream>

Preset::Preset()
{};

Preset::~Preset()
{
	animationTankPreset.clear();
	animationBulletPreset.clear();
	animationTankPreset.shrink_to_fit();
	animationBulletPreset.shrink_to_fit();
};

void Preset::LoadPreset(tankPreset type)
{
	this->type = type;
	switch (type)
	{
	case tankPreset::HEROTANK1:
		ReadFile("./data/tank/preset/Hero_preset1.ini");
		break;
	case tankPreset::HEROTANK2:
		ReadFile("./data/tank/preset/Hero_preset2.ini");
		break;
	case tankPreset::HEROTANK3:
		ReadFile("./data/tank/preset/WidthTank.ini");
		break;
	case tankPreset::ENEMYTANKEASY:
		ReadFile("./data/tank/preset/easyPreset.ini");
		break;
	case tankPreset::ENEMYTANKFAST:
		ReadFile("./data/tank/preset/fastPreset.ini");
		break;
	case tankPreset::ENEMYTANKPOWER:
		ReadFile("./data/tank/preset/powerTank.ini");
		break;
	case tankPreset::ENEMYTANKARMOR:
		ReadFile("./data/tank/preset/arrmorPreset.ini");
		break;
	case tankPreset::WIDTHTANK:
		ReadFile("./data/tank/preset/WidthTank.ini");
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