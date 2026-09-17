#pragma once
#include "StatTracker.h"

namespace CoinflipGame
{
	const struct VictoryData
	{
		const float multiplier;
	};

	int Play(StatTracker::Profits& aProfitStruct, StatTracker::Wins& aWinStruct);
}