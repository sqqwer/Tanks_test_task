#pragma once

#include "Framework.h"

class Object
{
public:
	Object();
	Object(float poss_x, float poss_y);

	virtual void PressKey(FRKey k) = 0;
	virtual void ReleasedKey() = 0;
	void Update(int w, int h, float spec);

	// function for get possition of object
	int GetX() const {
		return (int)possition_x;
	};
	int GetY() const {
		return (int)possition_y;
	};
	int& GetRefSizeW() {
		return size_h;
	};
	int& GetRefSizeH() {
		return size_w;
	};
	float GetvellX() const {
		return velocity_x;
	};
	float GetvellY() const {
		return velocity_y;
	};

protected:
	// velocity of object
	float velocity_x;
	float velocity_y;
private:
	int size_h;
	int size_w;
	// possition on map
	float possition_x;
	float possition_y;
};
