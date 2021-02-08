#pragma once

const float millToSec = (0.001f);

class Time
{
public:
	Time();
	Time(unsigned int (*GetTime)(void));
	float Mark();
private:
	unsigned int (*GetTime)(void);
	float last{};
};