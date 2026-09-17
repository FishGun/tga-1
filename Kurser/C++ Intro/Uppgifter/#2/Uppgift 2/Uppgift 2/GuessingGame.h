#pragma once
#include "StatTracker.h"

namespace GuessingGame
{
	const struct VictoryData
	{
		const int multiplier;
	};

	int Play(StatTracker::Profits& aProfitStruct, StatTracker::Wins& aWinStruct);
}