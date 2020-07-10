#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::Start()
{
	this->_timeStampStart = std::chrono::system_clock::now();
}

void Timer::Stop()
{
	this->_timeStampEnd = std::chrono::system_clock::now();
}

void Timer::Reset()
{
	auto now = std::chrono::system_clock::now();
	this->_timeStampStart = std::chrono::system_clock::now();
	this->_timeStampEnd = std::chrono::system_clock::now();
}

long long Timer::GetCount(TimeFormat format)
{
	switch (format)
	{
	case Timer::MICRO_SECONDS:
		return std::chrono::duration_cast<std::chrono::microseconds>(this->_timeStampEnd - this->_timeStampStart).count();
		break;
	case Timer::MILI_SECONDS:
		return std::chrono::duration_cast<std::chrono::milliseconds>(this->_timeStampEnd - this->_timeStampStart).count();
		break;
	case Timer::SECONDS:
		return std::chrono::duration_cast<std::chrono::seconds>(this->_timeStampEnd - this->_timeStampStart).count();
		break;
	case Timer::MINUTES:
		return std::chrono::duration_cast<std::chrono::minutes>(this->_timeStampEnd - this->_timeStampStart).count();
		break;
	case Timer::HOURS:
		return std::chrono::duration_cast<std::chrono::hours>(this->_timeStampEnd - this->_timeStampStart).count();
		break;
	default:
		return 0;
		break;
	}
}
