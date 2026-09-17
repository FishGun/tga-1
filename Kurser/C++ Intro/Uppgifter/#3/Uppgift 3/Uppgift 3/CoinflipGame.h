#pragma once
#include "StatTracker.h"

namespace CoinflipGame
{
	const struct PlayData
	{
		const float victoryMultiplier;
	};

	int Play(StatTracker::Stats& aStats, const PlayData& aPlayData);
}