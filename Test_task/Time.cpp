#include "Time.h"


Time::Time()
	:
	last(0.0f), GetTime(0)
{};

Time::Time(unsigned int (*GetTime)(void))
	:
	GetTime(GetTime)
{
	last = static_cast<float>(GetTime()) * millToSec;
};

float Time::Mark() {
	const float old = last;
	last = static_cast<float>(GetTime()) * millToSec;
	return last - old;
};