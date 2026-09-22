#pragma once
#include <array>



class RouletteGame
{
public:
	const struct VictoryMultipliers
	{
		float straight;
		float redBlack;
		float oddEven;
		float column;
	};

	RouletteGame();
	RouletteGame(int aMinBet, int aMaxBet, VictoryMultipliers aVictoryMultipliersStruct = { .straight = 36.0f, .redBlack = 2.0f,.oddEven = 2.0f,.column = 3.0f });

	enum class BetTypes
	{
		Straight,
		RedBlack,
		OddEven,
		Column,
		Count
	};

	enum class RouletteColor
	{
		Green,
		Red,
		Black,
		Count
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

	PlayerBets myBets;

	int Play(StatTracker::Stats& aStats, const PlayData& aPlayData);

	void BetLogicHandler(StatTracker::Profits& aProfitStruct, const int& aBoardSize);
	int WinningsLogicHandler(StatTracker::Stats& aStats, const PlayData& aPlayData, const int& aRolledNumber);
private:
	int myProfits;
	int myMaxWinnings;
	int myMinBet;
	int myMaxBet;
	VictoryMultipliers myVictoryMultipliersStruct;
};