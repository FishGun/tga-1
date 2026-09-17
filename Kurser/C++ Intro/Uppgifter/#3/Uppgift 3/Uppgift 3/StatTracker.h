#pragma once
#include "MenuEnums.h"

namespace StatTracker
{
	struct Profits
	{
		int profitArray[static_cast<int>(MenuEnums::GameOptions::Count) - 2];
		int money;
	};

	struct Wins
	{
		static const int gameHistoryArraySize = 5;
		int gameHistory[gameHistoryArraySize];
		int total;
	};

	struct Stats
	{
		Profits profits;
		Wins wins;
	};

	void AddGame(Wins& aWinStruct, const bool aDidWin);
}