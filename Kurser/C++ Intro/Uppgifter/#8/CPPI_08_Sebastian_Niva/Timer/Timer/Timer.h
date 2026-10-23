#pragma once

#include <cstdint>
#include <chrono>

namespace CommonUtilities
{
	class Timer
	{
	public:
		Timer(float aFixedTickTime = 1.f / 60.f);
		Timer(const Timer& aTimer) = delete;
		Timer& operator=(const Timer& aTimer) = delete;
		void Update();
		float GetDeltaTime() const;
		double GetTotalTime() const;
		int GetFixedRateTickDeltaCount() const;
		uint64_t GetFixedRateTickCount() const;
	private:
		const std::chrono::high_resolution_clock myClock;
		const std::chrono::high_resolution_clock::time_point myStartPoint;
		std::chrono::high_resolution_clock::time_point myDeltaPoint;
		const float myTickRate;
	};
}