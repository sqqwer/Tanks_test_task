#include "Object.h"

Object::Object()
	: 
	possition_x(0), possition_y(0),
	velocity_x(0.0f), velocity_y(0.0f)
{}

Object::Object(Sprite* obj, float poss_x, float poss_y)
	:
	object(obj), 
	possition_x(poss_x), possition_y(poss_y),
	velocity_x(0.0f), velocity_y(0.0f)
{}
// function for get possition of object
int Object::GetX() const {
	return (int)possition_x;
}

int Object::GetY() const {
	return (int)possition_y;
}
// Destructe sprite
Sprite* Object::SriteRef() {
	return object;
}