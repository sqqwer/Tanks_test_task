#pragma once

const float millToSec = (0.001f);

class Time
{
public:
	Time();
	~Time() { GetTime = nullptr; };
	Time(unsigned int (*GetTime)(void));
	float Mark();
private:
	float last{};
	unsigned int (*GetTime)(void);
};