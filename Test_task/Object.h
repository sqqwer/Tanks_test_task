#pragma once

#include "Framework.h"

class Object
{
public:
	Object();
	Object(float poss_x, float poss_y);
	// changed function for bullet
	virtual void PressKey(FRKey k) = 0;
	virtual void ReleasedKey() = 0;
	virtual void Update(int w, int h, float spec) = 0;
	// Destructe sprite
	Sprite* SriteRef();
	// function for get possition of object
	int GetX() const;
	int GetY() const;

	Sprite* object[2];
	int i = 0;
protected:
	// possition on map
	float possition_x;
	float possition_y;
	// Velocity for bullet
	float velocity_x;
	float velocity_y;

};
