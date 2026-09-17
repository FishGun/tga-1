#include "DisplayManager.h"
#include "StatTracker.h"
#include <iostream>

namespace DisplayManager
{
	void DisplayMoney(StatTracker::Profits& aProfitStruct)
	{
		std::cout << "You currently have " << aProfitStruct.money << "$ left.\n";
	}

	void DisplayHistory(StatTracker::Wins& aWinStruct, bool aInitialEmptyLine)
	{
		if (aInitialEmptyLine)
		{
			std::cout << "\n";
		}
		std::cout <<
			"Your last " << aWinStruct.gameHistoryArraySize << " games went like this:\n";

		for (int i = 0; i < aWinStruct.gameHistoryArraySize; i++)
		{
			if (aWinStruct.gameHistory[i] == 1)
			{
				std::cout << "Win!\n";
			}
			else if (aWinStruct.gameHistory[i] == -1)
			{
				std::cout << "Loss!\n";
			}
			else
			{
				std::cout << "N/A\n";
			}
		}
		std::cout << "\n";
	}
}