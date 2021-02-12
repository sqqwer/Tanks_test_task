#include "Object.h"

Object::Object()
	:
	possition_x(0), possition_y(0),
	velocity_x(0.0f), velocity_y(0.0f),
	size_w(0), size_h(0)
{};

Object::Object(const float poss_x, const float poss_y)
	:
	possition_x(poss_x), possition_y(poss_y),
	velocity_x(0.0f), velocity_y(0.0f), size_w(0), size_h(0)
{};

Object::Object(const float poss_x, const float poss_y,
	const int outOfScreenX, const int outOfScreenY
)
	:
	possition_x(poss_x), possition_y(poss_y),
	velocity_x(0.0f), velocity_y(0.0f), size_w(0), size_h(0),
	outOfScreenX(outOfScreenX), outOfScreenY(outOfScreenY)
{};
// Update possition
void Object::Update(int w, int h, float spec)
{
	possition_x += velocity_x * (spec);
	possition_y += velocity_y * (spec);
	const int right = (float)(possition_x) + size_w;
	if (possition_x < outOfScreenX)
	{
		possition_x = (float)(outOfScreenX);
	}
	else if (right >= w)
	{
		possition_x = (float)(w) - size_w;
	}
	const int bottom = (float)(possition_y) + size_h;
	if (possition_y < outOfScreenY)
	{
		possition_y = (float)(outOfScreenY);
	}
	else if (bottom >= h)
	{
		possition_y = (float)(h) - size_h;
	}
};

void Object::Colisium(
	const float possX, const float possY,
	const float width, const float height, const float mark
)
{
	if (
		possition_x + size_w - 1 >= possX &&
		possition_x + 1 <= possX + width
		)
	{
		if (
			possition_y + size_h - 1 >= possY &&
			possition_y + 1  <= possY + height
			)
		{
			possition_x -= (velocity_x)*mark;
			possition_y -= (velocity_y)*mark;
		}
	}
};

void Object::TankColisium(
	const float possX, const float possY,
	const float width, const float height, const float mark
)
{
	if (
		possition_x + size_w >= possX &&
		possition_x <= possX + width
		)
	{
		if (
			possition_y + size_h >= possY &&
			possition_y <= possY + height
			)
		{
			if (!velocity_y)
			{
				possition_x -= velocity_x * mark;
			}
			else if (!velocity_x)
			{
				possition_y -= velocity_y * mark;
			}
		}
	}
};
