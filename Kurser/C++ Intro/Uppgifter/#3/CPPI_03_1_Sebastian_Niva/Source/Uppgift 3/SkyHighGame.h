#pragma once
#include "StatTracker.h"

namespace SkyHighGame
{
	const struct PlayData
	{
		static const int multiplierArraySize = 8;
		const float multiplierArray[multiplierArraySize];
	};

	int Play(StatTracker::Stats& aStats, const PlayData& aPlayData);
}