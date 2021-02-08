#include "Object.h"

Object::Object()
	: 
	possition_x(0), possition_y(0),
	velocity_x(0.0f), velocity_y(0.0f),
	size_w(0), size_h(0)
{}

Object::Object(const float poss_x, const float poss_y)
	:
	possition_x(poss_x), possition_y(poss_y),
	velocity_x(0.0f), velocity_y(0.0f)
{}

// Update possition
void Object::Update(int w, int h, float spec)
{
	const int out = 30;
	possition_x += velocity_x * (spec);
	possition_y += velocity_y * (spec);
	const int right = static_cast<int>(possition_x) + size_w;
	if (possition_x < out)
	{
		possition_x = static_cast<float>(out);
	}
	else if (right >= w)
	{
		possition_x = static_cast<float>(w) - size_w;
	}
	const int bottom = static_cast<int>(possition_y) + size_h;
	if (possition_y < out)
	{
		possition_y = static_cast<float>(out);
	}
	else if (bottom >= h)
	{
		possition_y = static_cast<float>(h) - size_h;
	}
}