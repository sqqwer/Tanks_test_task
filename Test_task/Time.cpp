#include "Time.h"


Time::Time()
	:
	last(0.0f)
{}

Time::Time(unsigned int (*GetTime)(void))
	:
	GetTime(GetTime)
{
	last = GetTime() * (0.001);
}

float Time::Mark() {
	float old = last;
	last = GetTime() * (0.001);
	return last - old;
}