#pragma once
#include "StatTracker.h"
#include <array>



namespace RouletteGame
{
	enum class BetTypes
	{
		Straight,
		RedBlack,
		OddEven,
		Column,
		Length
	};

	enum class RouletteColor
	{
		Green,
		Red,
		Black,
		Length
	};

	const struct VictoryMultipliers
	{
		const float straight;
		const float redBlack;
		const float oddEven;
		const float column;
	};

	const struct PlayData
	{
		static const int boardSize = 37;
		RouletteColor colorArray[boardSize];
		VictoryMultipliers victoryMultipliers;
	};

	const struct PlayerBets
	{
		std::array<int, PlayData::boardSize> straight;
		std::array<int, 2> redBlack;
		std::array<int, 2> oddEven;
		std::array<int, 3> column;
		int straightTotal;
		int redBlackTotal;
		int oddEvenTotal;
		int columnTotal;
		int total;
	};

	int Play(StatTracker::Stats& aStats, const  PlayData& aPlayData);

	void BetLogicHandler(StatTracker::Profits& aProfitStruct, const int& aBoardSize, PlayerBets& aBets);
	int WinningsLogicHandler(StatTracker::Stats& aStats, const PlayData& aPlayData, const PlayerBets& aBets, const int& aRolledNumber);
}