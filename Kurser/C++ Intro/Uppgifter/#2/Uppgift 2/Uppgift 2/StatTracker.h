#pragma once

namespace StatTracker
{
	struct Profits
	{
		//Should idealy be GameOptions::Length - 3 instead of 4, but unsure how to do that.
		int profitArray[4];
		int money;
	};

	struct Wins
	{
		//Should idealy be gameHistoryArraySize instead of 5, but unsure how to do that.
		int gameHistory[5];
		int total;
		const int gameHistoryArraySize = 5;
	};

	void AddGame(Wins& aWinStruct, bool aDidWin);
}