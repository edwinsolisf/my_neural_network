#pragma once

#include <chrono>

class Timer
{
public:
	enum TimeFormat : char
	{
		MICRO_SECONDS = -2, MILI_SECONDS = -1, SECONDS = 0, MINUTES = 1, HOURS = 2
	};

	Timer();
	~Timer();

	void Start();
	void Stop();
	void Reset();

	long long GetCount(TimeFormat format);
private:
	std::chrono::time_point<std::chrono::system_clock> _timeStampStart;
	std::chrono::time_point<std::chrono::system_clock> _timeStampEnd;
};