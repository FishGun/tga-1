// Timer.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "Timer.h"

namespace CommonUtilities
{
	Timer::Timer(float aFixedTickTime) : myTickRate(aFixedTickTime), myClock(std::chrono::high_resolution_clock()), myStartPoint(myClock.now()) {}

	void Timer::Update()
	{
		myDeltaPoint = myClock.now();
	}
	float Timer::GetDeltaTime() const
	{
		return std::chrono::duration<float>(myClock.now() - myDeltaPoint).count();
	}
	double Timer::GetTotalTime() const
	{
		return std::chrono::duration<double>(myClock.now() - myStartPoint).count();
	}
	int Timer::GetFixedRateTickDeltaCount() const
	{
		return static_cast<int>(GetDeltaTime() / myTickRate);
	}
	uint64_t Timer::GetFixedRateTickCount() const
	{
		return static_cast<uint64_t>(GetTotalTime() / myTickRate);
	}
}