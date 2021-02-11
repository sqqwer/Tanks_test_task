#pragma once

#include "Hero.h"
#include "Block.h"

enum class powerUps {
	UPGRAGE,
	EXTRALIVE,
	STELLWALL,
	COUNT
};

class Upgrade : public Block
{
public:
	Upgrade();
	Upgrade(
		const char* name, const float possX, const float possY,
		void (*draw)(Sprite*, int, int)
	);
	void PowerUpsColisium(Hero& hero);
	// Markfunction
	void ClearMark() {
		last = 0;
	};
	float GetMark() const {
		return last;
	};
	void UpdateMark(const float mark) {
		last += mark;
	};
	float GetConstTime() const {
		return reloadTime;
	};
	void Draw() override;

private:
	void ReleasedKey() {};
	void PressKey(FRKey k) {};
private:
	float last{};
	float lifeTime{ 0.50f };
	float reloadTime{ 1.0f };
};

