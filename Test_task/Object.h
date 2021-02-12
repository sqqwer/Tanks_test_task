#pragma once

#include "Framework.h"

class Object
{
public:
	Object();
	Object(const float poss_x, const float poss_y);
	Object(const float poss_x, const float poss_y,
		const int outOfScreenX, const int outOfScreenY
	);

	virtual void Colisium(
		const float possX, const float possY,
		const float width, const float height,
		const float mark
	);
	virtual void TankColisium(
		const float possX, const float possY,
		const float width, const float height,
		const float mark
	);
	// virtual function
	virtual void PressKey(FRKey k) = 0;
	virtual void ReleasedKey() = 0;
	virtual void Update(int w, int h, float spec);
	// function for get possition of object
	void BackX(const float vell, const float mark) {
		possition_x -= vell * mark;
	};
	void BackY(const float vell, const float mark) {
		possition_y -= vell * mark;
	};
	void SetVellX(const float vellX) {
		velocity_x = vellX;
	};
	void SetVellY(const float vellY) {
		velocity_y = vellY;
	}
	int GetSpW() const {
		return size_w;
	};
	int GetSpH() const {
		return size_h;
	};
	int GetX() const {
		return (int)possition_x;
	};
	int GetY() const {
		return (int)possition_y;
	};
	int& GetRefSizeW() {
		return size_w;
	};
	int& GetRefSizeH() {
		return size_h;
	};
	float GetvellX() const {
		return velocity_x;
	};
	float GetvellY() const {
		return velocity_y;
	};
	// Seter x, y
	void SetPossitionX(const float posX) {
		possition_x = posX;
	};
	void SetPossitionY(const float posY) {
		possition_y = posY;
	};
protected:
	//
	int outOfScreenX{ 0 };
	int outOfScreenY{ 0 };
	// velocity of object
	float velocity_x;
	float velocity_y;
	//size of sprite
	int size_h;
	int size_w;
	// possition on map
	float possition_x;
	float possition_y;
};
