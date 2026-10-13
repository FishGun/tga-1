#pragma once
#include <cassert>

namespace CommonUtilities
{
	template <typename T>
	T Min(T aFirst, T aSecond) { return aFirst > aSecond ? aSecond : aFirst; }

	template <typename T>
	T Max(T aFirst, T aSecond) { return aFirst > aSecond ? aFirst : aSecond; }

	template <typename T>
	T Clamp(T aValue, T aMin, T aMax)
	{
		assert(aMin <= aMax && "Fatal Error: Clamp min value was greater than its max value.");
		return Min(Max(aValue, aMin), aMax);
	}

	template <typename T>
	T Abs(T aValue) { return aValue < 0 ? -aValue : aValue; }

	template <typename T>
	T& Swap(T& aFirst, T& aSecond)
	{
		T temp = aFirst;
		aFirst = aSecond;
		aSecond = temp;
		return aFirst;
	}

	template <typename T>
	T Lerp(T aStart, T aEnd, float aPercent) { return static_cast<T>(aStart + aPercent * (aEnd - aStart)); }
}