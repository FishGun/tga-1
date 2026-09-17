#pragma once
#include "StatTracker.h"

namespace SkyHighGame
{
	const struct VictoryData
	{
		const float multiplierArray[8];
		const int multiplierArraySize;
	};

	int Play(StatTracker::Profits& aProfitStruct, StatTracker::Wins& aWinStruct);
}