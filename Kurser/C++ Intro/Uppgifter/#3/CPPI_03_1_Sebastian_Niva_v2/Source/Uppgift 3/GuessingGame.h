#pragma once
#include "StatTracker.h"

namespace GuessingGame
{
	const struct PlayData
	{
		const int victoryMultiplier;
	};

	int Play(StatTracker::Stats& aStats, const PlayData& aPlayData);
}